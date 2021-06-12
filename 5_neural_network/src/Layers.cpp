#include <iostream>
#include <numeric>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "Layers.h"
using std::cout;
using std::endl;

void printMatrix(Matrix &m)
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[0].size(); j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}

void Linear::printWeight()
{
    for (int i = 0; i < perceptrons.size(); i++)
    {
        for (int j = 0; j < perceptrons[0].weights.size(); j++)
            cout << perceptrons[i].weights[j] << " ";
        cout << endl;
    }
}

std::random_device Perceptron::device;
std::default_random_engine Perceptron::generator(device());
std::normal_distribution<double> Perceptron::distribution(0.0, 0.003);

Perceptron::Perceptron(int inFeatures)
{
    weights = vector<double> (inFeatures, 0.0);
    bias = 0.0;
    for (auto &w : weights)
        w = distribution(generator);
}

double Perceptron::forward(vector<double> x)
{   
    assert(x.size() == weights.size());
    return std::inner_product(x.begin(), x.end(), weights.begin(), (double)0.0) + bias;
}

/* Implementation of Linear Layer */

Linear::Linear(int inFeatures, int outFeatures, double learningRate)
    : _inFeatures(inFeatures), _outFeatures(outFeatures), _learningRate(learningRate)
{   
    for (int i = 0; i < outFeatures; i++)
        perceptrons.emplace_back(Perceptron(inFeatures));
}

// INPUTS:
// - _x has shape (N, inFeatures) where N is the batch size
// OUTPUTS:
// - out has shape (N, outFeatures)
Matrix Linear::forward(Matrix _x)
{
    x.clear();
    x = _x;
    Matrix out (x.size(), vector<double>(_outFeatures, 0.0));
    for (int n = 0; n < x.size(); n++)
        for (int i = 0; i < _outFeatures; i++)
            out[n][i] = perceptrons[i].forward(x[n]);
    return out;
}

// INPUTS:
// - dout : The upstream derivative, shape: (N, outFeatures)
// OUTPUTS:
// - dx : Gradient with respect to x
Matrix Linear::backward(Matrix dout)
{
    // calculate derivative
    // dw = x.T x dout, shape: (outFeatures, inFeatures)
    Matrix dw (_outFeatures, vector<double>(_inFeatures, 0.0));
    for (int i = 0; i < _outFeatures; i++)
        for (int j = 0; j < _inFeatures; j++)
            for (int n = 0; n < x.size(); n++)
                dw[i][j] += x[n][j] * dout[n][i];

    vector<double> db (_outFeatures, 0.0);
    for (int i = 0; i < _outFeatures; i++)
        for (int n = 0; n < dout.size(); n++)
            db[i] += dout[n][i];

    // dw = dout x w, shape: (N, inFeatures)
    Matrix dx (dout.size(), vector<double>(_inFeatures, 0.0));
    for (int n = 0; n < dout.size(); n++)
        for (int j = 0; j < _inFeatures; j++)
            for (int i = 0; i < _outFeatures; i++)
                dx[n][j] += dout[n][i] * perceptrons[i].weights[j];


    // update weights
    for (int i = 0; i < _outFeatures; i++)
    {
        perceptrons[i].bias -= _learningRate * db[i];
        for (int j = 0; j < _inFeatures; j++)
            perceptrons[i].weights[j] -= _learningRate * dw[i][j];
    }
    
    return dx;
}

/* Implmentation of ReLU */

Matrix ReLU::forward(Matrix _x)
{
    x = _x;
    Matrix out (x.size(), vector<double>(x[0].size(), 0.0));
    for (int n = 0; n < x.size(); n++)
        for (int i = 0; i < x[n].size(); i++)
        {
            if (x[n][i] > 0)
                out[n][i] = x[n][i];
        }
    return out;
}

// INPUTS:
// - dout : The upstream derivative
Matrix ReLU::backward(Matrix dout)
{
    for (int n = 0; n < x.size(); n++)
        for (int i = 0; i < x[n].size(); i++)
        {
            if (x[n][i] < 0)
                dout[n][i] = 0;
        }
    return dout;
}

/* Implementation of SoftmaxLoss */

// Reference: https://gombru.github.io/2018/05/23/cross_entropy_loss/
double SoftmaxLoss::forward(Matrix _logits, vector<int> y)
{
    logits.clear();
    shiftlogits.clear();
    expshiftlogits.clear();
    logprobs.clear();
    probs.clear();

    logits = _logits;
    shiftlogits = Matrix (logits.size(), vector<double> (logits[0].size(), 0.0));
    double max;
    // Normalizing to avoid instability
    for (int i = 0; i < logits.size(); i++)
    {
        max = *std::max_element(logits[i].begin(), logits[i].end());
        for (int j = 0; j < logits[i].size(); j++)
            shiftlogits[i][j] = logits[i][j] - max;
    }

    // compute exponent
    expshiftlogits = Matrix (shiftlogits.size(), vector<double> (shiftlogits[0].size(), 0.0));
    for (int i = 0; i < shiftlogits.size(); i++)
        for (int j = 0; j < shiftlogits[i].size(); j++)
            expshiftlogits[i][j] = exp(shiftlogits[i][j]);

    // compute log probabilities
    double sum;
    logprobs = Matrix (shiftlogits.size(), vector<double> (shiftlogits[0].size(), 0.0));
    for (int i = 0; i < logprobs.size(); i++)
    {
        sum = std::accumulate(expshiftlogits[i].begin(), expshiftlogits[i].end(), (double)0.0);
        for (int j = 0; j < logprobs[i].size(); j++)
            logprobs[i][j] = shiftlogits[i][j] - log(sum);
    }

    // compute probability from log probability
    probs = Matrix (shiftlogits.size(), vector<double> (shiftlogits[0].size(), 0.0));
    for (int i = 0; i < logprobs.size(); i++)
        for (int j = 0; j < logprobs[i].size(); j++)
            probs[i][j] = exp(logprobs[i][j]);

    // compute cross entropy loss
    double loss = 0.0;
    for (int i = 0; i < logprobs.size(); i++) // for each data in the batch
        loss += logprobs[i][y[i]];
    loss *= -1.0 / logprobs.size();

    // cout << "Loss: " << loss << endl;
    // cout << "Out" << endl;
    // printMatrix(out);
    // cout << "Probs" << endl;
    // printMatrix(probs);
    return loss;
}

Matrix SoftmaxLoss::backward(vector<int> y)
{
    Matrix dloss(probs);
    for (int i = 0; i < dloss.size(); i++) // for each data in the batch
        dloss[i][y[i]] -= 1.0;

    for (int i = 0; i < dloss.size(); i++) // for each data in the batch
        for (int j = 0; j < dloss[i].size(); j++) // for each class
            dloss[i][j] /= dloss.size();
    
    // cout << "dloss" << endl;
    // printMatrix(dloss);
    return dloss;
}

void SoftmaxLoss::printProbs()
{
    cout << endl;
    cout << "logits" << endl;
    printMatrix(logits);
    cout << "Shiftlogits" << endl;
    printMatrix(shiftlogits);
    cout << "ExpShiftlogits" << endl;
    printMatrix(expshiftlogits);
    cout << "LogProbs" << endl;
    printMatrix(logprobs);
    cout << "Probs" << endl;
    printMatrix(probs);
}
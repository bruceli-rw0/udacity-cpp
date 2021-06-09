#include <iostream>
#include <numeric>
#include <cassert>
#include "Layers.h"
using std::cout;

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
        perceptrons[i].bias += _learningRate * db[i];
        for (int j = 0; j < _inFeatures; j++)
            perceptrons[i].weights[j] += _learningRate * dw[i][j];
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
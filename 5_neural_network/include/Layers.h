#ifndef LAYERS_H
#define LAYERS_H

#include <vector>
#include <random>
using std::vector;
using Matrix = vector<vector<double>>;

class Perceptron;
class Linear;

void printMatrix(Matrix &m);

class Perceptron
{
public:
    Perceptron(int inFeatures);
    double forward(vector<double> x);
    friend class Linear;

protected:
    vector<double> weights; // size: inFeatures
    double bias;

private:
    static std::random_device device;
    static std::default_random_engine generator;
    static std::normal_distribution<double> distribution;
};

class Linear
{
public:
    Linear(int inFeatures, int outFeatures, double learningRate);
    Matrix forward(Matrix _x);
    Matrix backward(Matrix dout);

private:
    void printWeight();

    int _inFeatures;
    int _outFeatures;
    double _learningRate;
    vector<Perceptron> perceptrons; // size: outFeatures
    Matrix x; // N x inFeatures
};

class ReLU
{
public:
    Matrix forward(Matrix _x);
    Matrix backward(Matrix dout);

private:
    Matrix x;
};

class SoftmaxLoss
{
public:
    double forward(Matrix _logits, vector<int> y);
    Matrix backward(vector<int> y);
    void printProbs();

private:
    Matrix logits;
    Matrix shiftlogits;
    Matrix expshiftlogits;
    Matrix logprobs;
    Matrix probs;
};

#endif
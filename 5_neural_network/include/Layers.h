#ifndef LAYERS_H
#define LAYERS_H

#include <vector>
#include <random>
using std::vector;

using KernelSize = std::tuple<int, int>;
using Kernel = vector<vector<double>>;
using Matrix = vector<vector<double>>;

class Linear;

class Perceptron
{
public:
    Perceptron(int inFeatures);
    double forward(vector<double> x);
    // int getSize() const { return weights.size(); }
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

// class Conv
// {
// public:
//     Conv
//     (
//         int inChannels, 
//         int outChannels, 
//         KernelSize kernelSize, 
//         int stride=1, 
//         int padding=0, 
//         bool useBias=true
//     ) {}
//     void forward();
//     void backward();

// private:
//     int inChannels;
//     int outChannels;
//     KernelSize kernelSize;
//     int stride;
//     int padding;
//     bool useBias;
//     vector<vector<Kernel>> weights;
//     vector<vector<double>> bias;
// };

// class ReLU3d
// {
// public:
//     void forward(vector<vector<vector<double>>> tensor);
//     void backward();
// };

// class MaxPool
// {
// public:
//     vector<vector<vector<double>>> forward(vector<vector<vector<double>>>);
//     void backward();

// private:
//     KernelSize kernelSize;
// };

#endif
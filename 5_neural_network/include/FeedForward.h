#ifndef FEEDFORWARD_H
#define FEEDFORWARD_H

#include "NeuralNetworks.h"

class TwoLayerNNClassifier : public NeuralNetworks<Matrix>
{
public:
    TwoLayerNNClassifier(int inputDim, vector<int> hiddenDim, int numClass, double learningRate=0.01);
    Matrix forward(Matrix x) override;
    void backward(Matrix dout) override;

private:
    vector<Linear> layers;
    ReLU relu;
};

class ThreeLayerNNClassifier : public NeuralNetworks<Matrix>
{
public:
    ThreeLayerNNClassifier(int inputDim, vector<int> hiddenDim, int numClass, double learningRate=0.01);
    Matrix forward(Matrix x) override;
    void backward(Matrix dout) override;

private:
    vector<Linear> layers;
    vector<ReLU> relu;
};

#endif
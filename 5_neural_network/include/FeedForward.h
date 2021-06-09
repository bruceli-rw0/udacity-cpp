#ifndef FEEDFORWARD_H
#define FEEDFORWARD_H

#include "NeuralNetworks.h"

class TwoLayerNet : public NeuralNetworks
{
public:
    TwoLayerNet(int inputDim, int hiddenDim, int numClass, double learningRate=0.01);
    virtual Matrix forward(Matrix x) override;
    virtual void backward(Matrix dout) override;

private:
    vector<Linear> layers;
    ReLU relu;
};


// class FeedForward : public NeuralNetworks
// {
// public:
//     FeedForward();
//     void forward();
//     void backward();
// };

#endif
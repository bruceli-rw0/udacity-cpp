#include "FeedForward.h"

TwoLayerNet::TwoLayerNet(int inputDim, int hiddenDim, int numClass, double learningRate)
{
    layers.emplace_back(Linear(inputDim, hiddenDim, learningRate));
    layers.emplace_back(Linear(hiddenDim, numClass, learningRate));
}

Matrix TwoLayerNet::forward(Matrix x)
{
    Matrix out;
    out = layers[0].forward(x);
    out = relu.forward(out);
    out = layers[1].forward(out);
    return out;
}

void TwoLayerNet::backward(Matrix dout)
{
    dout = layers[1].backward(dout);
    dout = relu.backward(dout);
    dout = layers[0].backward(dout);
}
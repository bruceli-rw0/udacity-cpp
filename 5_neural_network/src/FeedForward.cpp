#include "FeedForward.h"

TwoLayerNNClassifier::TwoLayerNNClassifier(int inputDim, vector<int> hiddenDim, int numClass, double learningRate)
{
    layers.emplace_back(Linear(inputDim, hiddenDim[0], learningRate));
    layers.emplace_back(Linear(hiddenDim[0], numClass, learningRate));
}

Matrix TwoLayerNNClassifier::forward(Matrix x)
{
    Matrix out;
    out = layers[0].forward(x);
    out = relu.forward(out);
    out = layers[1].forward(out);
    return out;
}

void TwoLayerNNClassifier::backward(Matrix dout)
{
    dout = layers[1].backward(dout);
    dout = relu.backward(dout);
    dout = layers[0].backward(dout);
}

ThreeLayerNNClassifier::ThreeLayerNNClassifier(int inputDim, vector<int> hiddenDim, int numClass, double learningRate)
{
    layers.emplace_back(Linear(inputDim, hiddenDim[0], learningRate));
    layers.emplace_back(Linear(hiddenDim[0], hiddenDim[1], learningRate));
    layers.emplace_back(Linear(hiddenDim[1], numClass, learningRate));

    relu.emplace_back(ReLU());
    relu.emplace_back(ReLU());
}

Matrix ThreeLayerNNClassifier::forward(Matrix x)
{
    Matrix out;
    out = layers[0].forward(x);
    out = relu[0].forward(out);
    out = layers[1].forward(out);
    out = relu[1].forward(out);
    out = layers[2].forward(out);
    return out;
}

void ThreeLayerNNClassifier::backward(Matrix dout)
{
    dout = layers[2].backward(dout);
    dout = relu[1].backward(dout);
    dout = layers[1].backward(dout);
    dout = relu[0].backward(dout);
    dout = layers[0].backward(dout);
}
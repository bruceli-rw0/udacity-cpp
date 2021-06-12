#ifndef NEURALNETWORKS_H
#define NEURALNETWORKS_H

#include "Layers.h"

/*
An abstract class of neural network. TensorType can be a matrix for feedforward 
neural network or it can a 3-dimensional tensor if using convolutional 
neural network.
*/
template <typename TensorType>
class NeuralNetworks
{
public:
    NeuralNetworks() {}
    virtual TensorType forward(TensorType x) = 0;
    virtual void backward(TensorType dout) = 0;
};

#endif
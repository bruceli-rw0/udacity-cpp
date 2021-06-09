#ifndef NEURALNETWORKS_H
#define NEURALNETWORKS_H

#include "Layers.h"

class NeuralNetworks
{
public:
    NeuralNetworks() {}
    virtual Matrix forward(Matrix x) = 0;
    virtual void backward(Matrix dout) = 0;
};

#endif
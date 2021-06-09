#include <iostream>
#include <memory>
#include "FeedForward.h"
using std::cout;

int main()
{
    std::cout << "------ Trained XOR Gate Example ------ \n";
    auto XORModel = std::make_unique<TwoLayerNet>(2, 10, 1);
    Matrix out;
    double dout;
    double mse;
    unsigned int iterations = 6000;
    for (unsigned int i = 0; i < iterations; i++)
    {
        mse = 0.0;
        
        // 4 training examples
        out = XORModel->forward({{0,0}});
        dout = 0.0 - out[0][0];
        XORModel->backward({{dout}});
        mse += 0.5 * dout * dout;

        out = XORModel->forward({{0,1}});
        dout = 1.0 - out[0][0];
        XORModel->backward({{dout}});
        mse += 0.5 * dout * dout;

        out = XORModel->forward({{1,0}});
        dout = 1.0 - out[0][0];
        XORModel->backward({{dout}});
        mse += 0.5 * dout * dout;

        out = XORModel->forward({{1,1}});
        dout = 0.0 - out[0][0];
        XORModel->backward({{dout}});
        mse += 0.5 * dout * dout;

        // average the loss
        mse = mse / 4.0;

        if (i % 300 == 0) // we should we the error drops every 100 iterations
            std::cout << "MSE: " << mse << "\n";
    }

    auto label = [](double x) { return (x > 0.5) ? 1 : 0; };
    std::cout << "\nPredictions:\n"; 
    std::cout << "0, 0 -> " << label(XORModel->forward({{0, 0}})[0][0]) << "\n";
    std::cout << "0, 1 -> " << label(XORModel->forward({{0, 1}})[0][0]) << "\n";
    std::cout << "1, 0 -> " << label(XORModel->forward({{1, 0}})[0][0]) << "\n";
    std::cout << "1, 1 -> " << label(XORModel->forward({{1, 1}})[0][0]) << "\n";


    return 0;
}
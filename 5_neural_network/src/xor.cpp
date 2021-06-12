#include <iostream>
#include <memory>
#include "FeedForward.h"
using std::cout;
using std::endl;

int main()
{
    std::cout << "------ Trained XOR Gate Example ------ \n";
    Matrix data = {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };
    vector<double> labels {0.0, 1.0, 1.0, 0.0};

    vector<int> hiddenSize = {10};
    auto XORModel = std::make_unique<TwoLayerNNClassifier>(2, hiddenSize, 1, 0.1);
    Matrix out;
    Matrix dout;
    double mse;
    unsigned int iterations = 6000;
    for (unsigned int i = 0; i < iterations; i++)
    {
        mse = 0.0;
        
        // 4 training examples
        out = XORModel->forward(data);
        dout = vector<vector<double>> (4, vector<double> (1, 0.0));
        for (int i = 0; i < 4; i++)
        {
            dout[i][0] = out[i][0] - labels[i];
            mse += 0.5 * dout[i][0] * dout[i][0];
        }
        XORModel->backward(dout);

        // average the loss
        mse = mse / 4.0;

        if (i % 300 == 0) // we should we the error drops every 300 iterations
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
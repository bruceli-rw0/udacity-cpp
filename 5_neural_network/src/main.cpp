#include <iostream>
#include <memory>
#include "FeedForward.h"
using std::cout;

int main()
{
    auto network = std::make_unique<TwoLayerNet>(10, 20, 4);
    Matrix x = {
        {1,2,3,4,5,6,7,8,9,10},
        {9,8,7,6,5,4,3,2,1,0}
    };
    Matrix y = {
        {0,0,0,1},
        {1,0,0,0}
    };

    Matrix out = network->forward(x);
    for (auto &r : out)
    {
        for (auto &c : r)
            cout << c << "\t";
        cout << "\n";
    }

    Matrix dout (out.size(), vector<double>(out[0].size(), 0.0));
    for (int i = 0; i < dout.size(); i++)
        for (int j = 0; j < dout[i].size(); j++)
            dout[i][j] = y[i][j] - out[i][j];

    network->backward(dout);

    return 0;
}
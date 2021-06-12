#include <iostream>
#include <memory>
#include <algorithm>
#include "FeedForward.h"
#include "Datasets.h"
#include "Layers.h"
using std::cout;
using std::endl;

Matrix normalize(Matrix image);

int main()
{
    string folder = "../fashion-mnist/";
    auto data = getImage1D(folder + "train-images-idx3-ubyte");
    auto labels = getLabel(folder + "train-labels-idx1-ubyte");
    auto testdata = getImage1D(folder + "t10k-images-idx3-ubyte");
    auto testlabels = getLabel(folder + "t10k-labels-idx1-ubyte");
    cout << "Finished loading data ..." << endl;
    data = normalize(data);
    testdata = normalize(testdata);
    cout << "Finished normalizing images ..." << endl;

    int inputSize = 28 * 28;
    int numClasses = 10;
    // auto network = std::make_unique<TwoLayerNNClassifier>(inputSize, vector<int> {50}, numClasses);
    auto network = std::make_unique<ThreeLayerNNClassifier>(inputSize, vector<int> {512, 512}, numClasses);
    auto criterion = std::make_unique<SoftmaxLoss>();

    Matrix x; // batch image
    vector<int> y; // batch label
    Matrix out;
    Matrix dout;
    double loss; // softmax loss
    int batchSize = 32;
    int printPerIter = 100;
    int iterations = data.size() / batchSize;
    int epochs = 20;

    cout << "Data size: " << data.size() << endl;
    cout << "Batch size: " << batchSize << endl;
    cout << "Number of iterations per epoch: " << iterations << endl << endl;;

    for (int e = 0; e < epochs; e++)
    {
        cout << "Epoch: " << e+1 << " ..." << endl;
        // train model
        loss = 0.0;
        for (int i = 0; i < iterations; i++)
        {
            int begin = i * batchSize;
            int end = (i+1) * batchSize;
            x = Matrix (data.begin() + begin, data.begin() + end);
            y = vector<int> (labels.begin() + begin, labels.begin() + end);
            out = network->forward(x);
            loss += criterion->forward(out, y);
            
            dout = criterion->backward(y);
            network->backward(dout);

            if ((i+1) % printPerIter == 0)
            {
                // criterion->printProbs();
                cout << "Iter: " << i+1 << "\tLoss: " << loss / printPerIter << "\n";
                loss = 0.0;
            }
        }
        
        // test model
        double testloss = 0.0;
        int acc = 0;
        for (int i = 0; i < testdata.size(); i++)
        {
            x = Matrix (testdata.begin() + i, testdata.begin() + i+1);
            y = vector<int> (testlabels.begin() + i, testlabels.begin() + i+1);
            out = network->forward(x);
            testloss += criterion->forward(out, y);

            int argmax = std::distance(out[0].begin(), std::max_element(out[0].begin(), out[0].end()));
            if (argmax == y[0])
                acc += 1;
        }
        cout << "Test loss: " << testloss / testdata.size() << "\t";
        cout << "Test accuracy: " << acc << "/" << testdata.size() << " = " << (double)acc / testdata.size() * 100 << "%" << endl;
        cout << endl;
    }

    return 0;
}

Matrix normalize(Matrix image)
{
    Matrix normImage (image.size(), vector<double> (image[0].size(), 0.0));
    double sum;
    double mean;
    double std;
    for (int i = 0; i < image.size(); i++)
    {
        sum = std::accumulate(image[i].begin(), image[i].end(), 0.0);
        mean = sum / image[i].size();
        std = 0.0;
        for (int j = 0; j < image[i].size(); j++)
            std += pow(image[i][j] - mean, 2);
        std = sqrt(std / 10.0);

        for (int j = 0; j < image[i].size(); j++)
            normImage[i][j] = (image[i][j] - mean) / std;
    }
    return normImage;
}
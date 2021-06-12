#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "Datasets.h"
using std::cout;

uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

void getInfo
(
    std::ifstream& image_file,
    uint32_t& magic,
    uint32_t& num_items,
    uint32_t& rows,
    uint32_t& cols
)
{
    image_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);

    // 2051 is magic number for images
    if(magic != 2051)
    {
        cout << "Incorrect image file magic: " << magic << "\n";
        exit(0);
    }

    image_file.read(reinterpret_cast<char*>(&num_items), 4);
    num_items = swap_endian(num_items);
    image_file.read(reinterpret_cast<char*>(&rows), 4);
    rows = swap_endian(rows);
    image_file.read(reinterpret_cast<char*>(&cols), 4);
    cols = swap_endian(cols);
}

// Reference for loading MNIST data:
// https://compvisionlab.wordpress.com/2014/01/01/c-code-for-reading-mnist-data-set/
Matrix getImage1D(const std::string& filename)
{
    // Open files
    std::ifstream image_file(filename, std::ios::in | std::ios::binary);

    // Read the magic and the meta data
    uint32_t magic;
    uint32_t num_items;
    uint32_t rows;
    uint32_t cols;
    getInfo(image_file, magic, num_items, rows, cols);

    Matrix data (num_items, vector<double> (rows * cols, 0.0));
    for(int i = 0; i < num_items; ++i)
        for(int r = 0; r < rows; ++r)
            for(int c = 0; c < cols; ++c)
            {
                unsigned char temp = 0;
                image_file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                data[i][r*cols + c] = (double)temp;
            }
    return data;
}

vector<Matrix> getImage2D(const std::string& filename)
{
    // Open files
    std::ifstream image_file(filename, std::ios::in | std::ios::binary);

    // Read the magic and the meta data
    uint32_t magic;
    uint32_t num_items;
    uint32_t rows;
    uint32_t cols;
    getInfo(image_file, magic, num_items, rows, cols);

    vector<Matrix> data (num_items, Matrix (rows, vector<double> (cols, 0.0)));
    for(int i = 0; i < num_items; ++i)
        for(int r = 0; r < rows; ++r)
            for(int c = 0; c < cols; ++c)
            {
                unsigned char temp = 0;
                image_file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                data[i][r][c] = (double)temp;
            }
    return data;
}

vector<int> getLabel(const std::string& filename)
{
    std::ifstream label_file(filename, std::ios::in | std::ios::binary);

    uint32_t magic;
    uint32_t num_labels;

    label_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);

    // 2049 is magic number for images
    if(magic != 2049)
    {
        cout<<"Incorrect label file magic: "<< magic << std::endl;
        exit(0);
    }

    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);

    vector<int> labels (num_labels, 0.0);
    for(int i = 0; i < num_labels; ++i)
    {
        unsigned char temp = 0;
        label_file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        labels[i] = (int)temp;
    }
    return labels;
}
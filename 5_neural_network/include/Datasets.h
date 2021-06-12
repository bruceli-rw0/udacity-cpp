#ifndef DATASETS_H
#define DATASETS_H

#include <string>
#include "Layers.h"
using std::string;

Matrix getImage1D(const string& filename);
vector<Matrix> getImage2D(const string& filename);
vector<int> getLabel(const string& filename);

#endif
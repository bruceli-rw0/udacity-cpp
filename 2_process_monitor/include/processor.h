#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
using std::vector;

class Processor {
public:
    float Utilization();

private:
    vector<long> stat {0,0,0,0,0,0,0,0,0,0};
    vector<long> prev_stat {0,0,0,0,0,0,0,0,0,0};
};

#endif

#pragma once
#include "dpacalc.h"
#include <iostream>
#include <mutex>

using namespace Eigen;
using namespace std;
namespace SamplesInput {
class base {
public:
    unsigned long long SamplesPerTrace; //from metadata, dimension N of matrix T
    unsigned long long NumTraces; //dimension N of matrix T
    unsigned long long CurrentSample;  //dimension N of matrix T
    base(int _input) {
        assert(_input != -1);
        input=_input;
        CurrentSample=0;
        CurrentId=-1;
    }

    virtual unsigned long long read(unsigned long long *id, shared_ptr<TracesMatrix> *traces) = 0;
    virtual shared_ptr<DataMatrix> readData() = 0;
    virtual void populateQueue(){};

protected:
    int input;
    shared_ptr<DataMatrix> data;
    unsigned long long CurrentId;
    std::mutex input_mutex;
};

}

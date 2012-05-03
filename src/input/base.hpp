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
    base(shared_ptr<istream> _input) {
        assert(_input.get() != NULL);
        input=shared_ptr<istream>(_input);
        CurrentSample=0;
        CurrentId=-1;
    }

    virtual unsigned long long read(unsigned long long num,unsigned long long *id, shared_ptr<TracesMatrix> *traces) = 0;
    virtual shared_ptr<DataMatrix> readData() = 0;

protected:
    shared_ptr<istream> input;
    shared_ptr<DataMatrix> data;
    unsigned long long CurrentId;
    std::mutex input_mutex;
};

}
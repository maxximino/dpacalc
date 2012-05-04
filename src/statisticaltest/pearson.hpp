#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "dpacalc.h"
#include "base.hpp"
#include <map>
using namespace Eigen;
using namespace std;
namespace Statistic {
struct BatchInfo {
public:
    shared_ptr<TracesMatrix> traces;
    unsigned long numvalid;
    Matrix<TraceValueType,BATCH_SIZE,1> blktraceaverage;
};

class pearson : public base {
public:
    virtual void parallel_pass1(unsigned long long batchid,shared_ptr<TracesMatrix> &traces,unsigned long numvalid);
    virtual void single_pass2();
    virtual void parallel_pass3(unsigned long long batchid);
    virtual void sequential_printCSV(unsigned long long batchid,ostream & out);
    pearson(shared_ptr<PowerModelMatrix> &_pm,unsigned long long nt);
protected:
    std::map<unsigned long long,shared_ptr<BatchInfo> > batches;
    Matrix<TraceValueType,Dynamic,1> pmaverage;
    Matrix<TraceValueType,Dynamic,1> traceaverage;
};
}


#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "config.h"
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace SamplesInput {
class bin1 : public base {
public:
    virtual unsigned long long read(unsigned long long num,unsigned long long *id, shared_ptr<TracesMatrix>traces, shared_ptr<DataMatrix> knowndata);
    bin1(istream *_input);


};
}

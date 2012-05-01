#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "config.h"
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace GenerateIntermediateValues {
class int1 : public base {
public:
    virtual void generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval);
    int1(shared_ptr<KeyGenerators::KEYGENCLASS> _keygen): base(_keygen) {}
};
}


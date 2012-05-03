#pragma once
#include <iostream>
#include <mutex>
#include "dpacalc.h"
using namespace Eigen;
using namespace std;
namespace GenerateIntermediateValues {
class base {
public:
    virtual void generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)=0;
    base(shared_ptr<KeyGenerators::KEYGENCLASS> _keygen): keygen(_keygen) {}
protected:
    shared_ptr<KeyGenerators::KEYGENCLASS> keygen;
};
}

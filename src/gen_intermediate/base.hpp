#pragma once
#include <iostream>
#include <mutex>
#include "dpacalc.h"
using namespace Eigen;
using namespace std;
namespace GenerateIntermediateValues {
class base {
public:
    base(TCLAP::CmdLine &cmd,shared_ptr<KeyGenerators::KEYGENCLASS> _keygen):keygen(_keygen) {};
    virtual void init() {};

    virtual void generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)=0;

protected:
    shared_ptr<KeyGenerators::KEYGENCLASS> keygen;
};
}

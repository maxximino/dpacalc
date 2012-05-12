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
    virtual void init();
    int1(TCLAP::CmdLine &cmd, shared_ptr<KeyGenerators::base> _keygen): base(cmd,_keygen), whichsboxArg("b","sbox","Which SBOX output should I correlate?",false,0,"0-15") {
        cmd.add(whichsboxArg);
    }
protected:
    TCLAP::ValueArg<int> whichsboxArg;
};
}


#pragma once
#include "dpacalc.h"
#include "keygen/base.hpp"
using namespace std;
namespace Output {
class base {
public:
    base(TCLAP::CmdLine &cmd,shared_ptr<KeyGenerators::base> _keygen):keygen(_keygen) {};
    virtual void init() {};
    virtual void WriteBatch(unsigned long long id,shared_ptr<StatisticIndexMatrix> &s)=0;
    virtual void end() {};

protected:
    shared_ptr<KeyGenerators::base> keygen;
};

}

#pragma once
#include "dpacalc.h"
#include "base.hpp"
using namespace std;
namespace Output {
class multiple: public base {
public:
    multiple(TCLAP::CmdLine &cmd,shared_ptr<KeyGenerators::base> _keygen);
    virtual void init();
    virtual void end();
    virtual void WriteBatch(unsigned long long id,shared_ptr<StatisticIndexMatrix> &s);
protected:
    std::vector<shared_ptr<Output::base> > outputs;

};

}

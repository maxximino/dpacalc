#pragma once
#include "dpacalc.h"

namespace Output {
class base {
public:
    base(TCLAP::CmdLine &cmd) {};
    virtual void init() {};
    virtual void WriteBatch(unsigned long long id,shared_ptr<StatisticIndexMatrix> &s)=0;
    virtual void end() {};
};

}

#pragma once
#include "dpacalc.h"
#include "base.hpp"

namespace Output {
class gnuplot: public base {
public:
    gnuplot(TCLAP::CmdLine &cmd):base(cmd),
        dataNameArg("o","output","Gnuplot data file name",true,"","path"),
        scriptNameArg("s","script-output","Gnuplot script output file name",true,"","path")
    {
        cmd.add(dataNameArg);
        cmd.add(scriptNameArg);
    };
    virtual void init();
    virtual void WriteBatch(unsigned long long id,shared_ptr<StatisticIndexMatrix> &s);
protected:
    TCLAP::ValueArg<std::string> dataNameArg;
    TCLAP::ValueArg<std::string> scriptNameArg;
};

}

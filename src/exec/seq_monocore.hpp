#pragma once
#include "dpacalc.h"
#include "base.hpp"

namespace ExecMethod {
class seq_monocore: public base {
public:
    virtual void RunAndWait(unsigned long numberoftimes);  //What should I run? DPA::onRun(); called on the right thread.
};

}

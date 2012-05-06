#pragma once
#include "dpacalc.h"

namespace ExecMethod {
class base {
public:
    virtual void RunAndWait(unsigned long numberoftimes)=0;  //What should I run? DPA::onRun(); called on the right thread.
};

}

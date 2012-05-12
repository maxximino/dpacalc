#pragma once
#include "base.hpp"
#include "dpacalc.h"
#include <bitset>
#include <iostream>
namespace KeyGenerators {
class keygen1:public base {
public:
    keygen1(TCLAP::CmdLine &cmd):base(cmd),shiftbitsArgs("k","shiftkey","Shift key hypotesis bits on the left by X bits",false,0,"int") {
        cmd.add(shiftbitsArgs);
    };
    virtual void init();
    virtual KeyDataType getKeyFromIndex(KeyIndexType idx) ;

protected:
    TCLAP::ValueArg<int> shiftbitsArgs;
};
}

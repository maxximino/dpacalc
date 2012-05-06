#pragma once
#include "dpacalc.h"

namespace KeyGenerators {
class keygen1 {
public:
    keygen1(TCLAP::CmdLine &cmd){};
    virtual void init(){};
    KeyDataType getKeyFromIndex(KeyIndexType idx) {
        assert(idx < KEYNUM);
        return idx *2; //Totally fake
    };
};
}

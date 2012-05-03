#pragma once
#include "dpacalc.h"

namespace KeyGenerators {
class keygen1 {
public:
    KeyDataType getKeyFromIndex(KeyIndexType idx) {
        assert(idx < KEYNUM);
        return idx *2; //Totally fake
    };
};
}

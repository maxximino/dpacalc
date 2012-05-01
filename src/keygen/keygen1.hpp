#pragma once
#include "config.h"

namespace KeyGenerators {
class keygen1 {
public:
    KeyDataType getKeyFromIndex(KeyIndexType idx) {
        assert(idx < KEYNUM);
        return idx *3; //Totally fake
    };
};
}

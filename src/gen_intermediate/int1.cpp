#include "dpacalc.h"
#include "int1.hpp"
#include "aes.h"
#include <iostream>
void GenerateIntermediateValues::int1::init()
{
    if(whichsboxArg.getValue() >15 || whichsboxArg.getValue() < 0) {
        cerr << "In AES you have only 16 SBOXes (0-15)." <<endl;
        exit(1);
    }
}

void GenerateIntermediateValues::int1::generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)
{
    std::bitset<KEY_SIZE_BIT> key;
    uint8_t fullaeskey[AES_STATE_BYTES_NO];
    uint8_t fullaesdata[AES_STATE_BYTES_NO];
    memset(fullaeskey,0,AES_STATE_BYTES_NO);
    uint8_t UnrolledRoundKey[AES_128_ROUND_KEY_NO][AES_STATE_BYTES_NO];
    uint8_t * dataptr = &fullaesdata[whichsboxArg.getValue()];
    for(KeyIndexType keyidx=0; keyidx < KEYNUM ; ++keyidx) {
        key=keygen->getKeyFromIndex(keyidx);
        BitsetToBuffer<KEY_SIZE_BYTE>(key,(char*)&fullaeskey);
        KeyExpansion(fullaeskey,UnrolledRoundKey);
        for(unsigned long trcidx = 0; trcidx < knowndata->size(); trcidx++) {
            BitsetToBuffer<DATA_SIZE_BYTE>((*knowndata)[trcidx],(char*)&fullaesdata);
            AddRoundKey(fullaesdata,UnrolledRoundKey[0]);
            (*intval)(trcidx,keyidx) = SBOX[*dataptr];

        }
    }
}


#include "dpacalc.h"
#include "int1.hpp"
#include "aes.h"

void GenerateIntermediateValues::int1::generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)
{
    uint8_t fullaeskey[AES_STATE_BYTES_NO];
    uint8_t fullaesdata[AES_STATE_BYTES_NO];
    memset(fullaeskey,0,AES_STATE_BYTES_NO);
    unsigned long long* fullaeskey_ptr = (unsigned long long*)fullaeskey;
    uint8_t UnrolledRoundKey[AES_128_ROUND_KEY_NO][AES_STATE_BYTES_NO];
    for(KeyIndexType keyidx=0; keyidx < KEYNUM ; ++keyidx) {
      *(fullaeskey_ptr)=keygen->getKeyFromIndex(keyidx); //Last 64 bit always at zero. Endianness problem.
      KeyExpansion(fullaeskey,UnrolledRoundKey);
    for(unsigned long trcidx = 0; trcidx < knowndata->size(); trcidx++) {
            BitsetToBuffer<DATA_SIZE_BYTE>((*knowndata)[trcidx],(char*)&fullaesdata);
            AddRoundKey(fullaesdata,fullaeskey);
            (*intval)(trcidx,keyidx) = SBOX[fullaesdata[0]];

        }
    }
}


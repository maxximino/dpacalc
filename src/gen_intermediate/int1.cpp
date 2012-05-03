#include "dpacalc.h"
#include "int1.hpp"
void GenerateIntermediateValues::int1::generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)
{
    //unsigned long tmp;
    for(long trcidx = 0; trcidx < intval->rows(); trcidx++) {
        for(KeyIndexType keyidx=0; keyidx < KEYNUM ; ++keyidx) {

            (*intval)(trcidx,keyidx) = (*knowndata)[trcidx].count() * keygen->getKeyFromIndex(keyidx);
        }
    }
}

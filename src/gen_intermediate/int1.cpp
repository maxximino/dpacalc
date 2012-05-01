#include "int1.hpp"
#include "config.h"
#include "keygen/keygen1.hpp"
#include <mutex>
#include <Eigen/Dense>
void GenerateIntermediateValues::int1::generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)
{
    for(KeyIndexType i=0; i < KEYNUM ; ++i) {
        intval->col(i) = knowndata->cast<IntermediateValueType>() *2* keygen->getKeyFromIndex(i);
    }
}

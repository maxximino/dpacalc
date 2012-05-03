#include "dpacalc.h"
#include "pm1.hpp"
void GeneratePowerModel::pm1::generate(shared_ptr<IntermediateValueMatrix> &intval,shared_ptr<PowerModelMatrix> &pm)
{
    (*pm) = intval->cast<float>();
    (*pm) = pm->array() + 1;
    (*pm) = pm->array().sqrt() * 2 + pm->array().log();
}

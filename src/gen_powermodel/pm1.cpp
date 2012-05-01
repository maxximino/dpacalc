#include "pm1.hpp"
#include "config.h"
#include "keygen/keygen1.hpp"
#include <mutex>
#include <Eigen/Dense>
void GeneratePowerModel::pm1::generate(shared_ptr<IntermediateValueMatrix> &intval,shared_ptr<PowerModelMatrix> &pm)
{
    (*pm) = intval->cast<float>();
    (*pm) = pm->array() + 1;
    (*pm) = pm->array().sqrt() * 2 + pm->array().log();
}

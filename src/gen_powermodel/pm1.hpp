#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "config.h"
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace GeneratePowerModel {
class pm1 : public base {
public:
    virtual void generate(shared_ptr<IntermediateValueMatrix> &intval,shared_ptr<PowerModelMatrix> &pm);
    pm1():base() {}
};
}

#include <iostream>
#include <Eigen/Dense>
#include <memory>
#include "config.h"
using namespace Eigen;
using namespace std;
namespace GeneratePowerModel {
class base {
public:
    virtual void generate(shared_ptr<IntermediateValueMatrix> &intval,shared_ptr<PowerModelMatrix> &pm)=0;
    base() {}
protected:

};
}

#include <iostream>
#include <Eigen/Dense>
#include "config.h"
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace SamplesInput {
class bin1 : public base {
public:
    virtual unsigned long long read(unsigned long long num,unsigned long long *id, shared_ptr<Matrix<TRACETYPE,BATCH_SIZE,Dynamic> >traces, shared_ptr<Matrix<DATATYPE,BATCH_SIZE,1> > knowndata);
    bin1(istream *_input);


};
}

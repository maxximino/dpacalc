#pragma once
#include "dpacalc.h"
using namespace Eigen;
using namespace std;
namespace Statistic {
class base {
public:
    virtual void parallel_pass1(unsigned long long batchid,shared_ptr<TracesMatrix> &traces,unsigned long numvalid)=0;
    virtual void single_pass2()=0;
    virtual void parallel_pass3(unsigned long long batchid)=0;
    virtual void sequential_printCSV(unsigned long long batchid,ostream & out)=0;
    base(shared_ptr<PowerModelMatrix> &_pm, unsigned long long nt) {
        pm=shared_ptr<PowerModelMatrix>(_pm);
        NumTraces=nt;
    }
protected:
    shared_ptr<PowerModelMatrix> pm;
    unsigned long long NumTraces;
};
}

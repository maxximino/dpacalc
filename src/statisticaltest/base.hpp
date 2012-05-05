#pragma once
#include "dpacalc.h"
using namespace Eigen;
using namespace std;
namespace Statistic {
class base {
public:
    virtual void generate(shared_ptr<Eigen::Block<StatisticIndexMatrix,BATCH_SIZE,KEYNUM,1,1> > stat,shared_ptr<TracesMatrix> &traces,unsigned long numvalid)=0;
    base(shared_ptr<PowerModelMatrix> &_pm) {
        pm=shared_ptr<PowerModelMatrix>(_pm);
    }
protected:
    shared_ptr<PowerModelMatrix> pm;
};
}

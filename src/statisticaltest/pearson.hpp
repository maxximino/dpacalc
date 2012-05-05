#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "dpacalc.h"
#include "base.hpp"
#include <map>
using namespace Eigen;
using namespace std;
namespace Statistic {
class pearson : public base {
public:
    virtual void generate(shared_ptr<Eigen::Block<StatisticIndexMatrix,BATCH_SIZE,KEYNUM,1,1> > stat,shared_ptr<TracesMatrix> &traces,unsigned long numvalid);
    pearson(shared_ptr<PowerModelMatrix> &_pm);
protected:
    Eigen::Matrix<TraceValueType,Eigen::Dynamic,KEYNUM> pmexpect;
    Eigen::Matrix<TraceValueType,Eigen::Dynamic,KEYNUM> pmexpect_squared;
};
}


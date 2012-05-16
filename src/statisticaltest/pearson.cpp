#include "dpacalc.h"
#include "pearson.hpp"

void Statistic::pearson::init(shared_ptr< PowerModelMatrix >& _pm)
{
    Statistic::base::init(_pm);
    Eigen::Matrix<TraceValueType,1,KEYNUM> pmaverage = Matrix<TraceValueType,1,KEYNUM> ();
    pmexpect = Matrix<TraceValueType,Dynamic,KEYNUM> ( pm->rows(),KEYNUM );
    for ( long d = 0; d < KEYNUM; d++ )
    {
        pmaverage ( 0,d ) = pm->col(d).array().sum() / pm->col(d).array().count();
    }
    for (long d = 0; d < pm->cols(); d++ )
    {
        pmexpect.col(d) = pm->col(d).array() - pmaverage(0,d);
    }
    for (long keyh = 0; keyh < KEYNUM; keyh++ ) {
        pmexpect_bykey(0,keyh) = pmexpect.col(keyh).squaredNorm();
    }

}

void Statistic::pearson::generate(shared_ptr<StatisticIndexMatrix> &stat, shared_ptr< TracesMatrix >& traces, long unsigned int numvalid)
{
    /*PSEUDOCODE:
     For each time instant:
     Calculating averages avg(t(j))
     For each time and key hypotesis:
    stat(j,l) = dividend/divisor
    dividend = sum(i){t(i,j)-mediat(j))*pmexpect(i,l)}
    divisor = sqrt(sum(i)^2{t(i,j)-*mediat(j)} * sum(i){pmexpect_squared(i,l)} )
    Real code calculates all dividens and divisors together for each row, and then divides entire rows,
    to enable Eigen to better optimize those operations.
    */
    assert(numvalid <= BATCH_SIZE);
    TraceValueType tavg;
    auto dividendi = shared_ptr<Matrix<StatisticValueType,1,KEYNUM> >(new Matrix<StatisticValueType,1,KEYNUM>() );
    auto divisori = shared_ptr<Matrix<StatisticValueType,1,KEYNUM> >(new Matrix<StatisticValueType,1,KEYNUM>() );
    for(unsigned long long time=0; time < numvalid; time++) {
        tavg = traces->col(time).array().sum() / traces->col(time).array().count();
        (*divisori) = ((traces->col(time).array() - tavg).matrix().squaredNorm() * pmexpect_bykey).array().sqrt();
        (*dividendi).noalias() = (traces->col(time).array() - tavg).matrix().transpose() * pmexpect;
        stat->row(time) = (*dividendi).array() / (*divisori).array();

    }
}


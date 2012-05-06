#include "dpacalc.h"
#include "pearson.hpp"

void Statistic::pearson::init(shared_ptr< PowerModelMatrix >& _pm)
{
    Statistic::base::init(_pm);
    Eigen::Matrix<TraceValueType,1,KEYNUM> pmaverage = Matrix<TraceValueType,1,KEYNUM> ();
    pmexpect = Matrix<TraceValueType,Dynamic,KEYNUM> ( pm->rows(),KEYNUM );
    for ( long d = 0; d < KEYNUM; d++ )
    {
        //Rischio di sum overflow? si può fare approccio tipo ricerca binaria, ma efficienza cala.
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

void Statistic::pearson::generate(shared_ptr< Eigen::Block<StatisticIndexMatrix,BATCH_SIZE,KEYNUM,1,1> > stat, shared_ptr< TracesMatrix >& traces, long unsigned int numvalid)
{
    /*PSEUDOCODE:
     per ogni istante di tempo:
     Calcolarsi medie avg(t(j))
     Per ogni tempo e ipotesi di chiave:
    stat(j,l) = dividendo/divisore
    dividendo = sum(i){t(i,j)-mediat(j))*pmexpect(i,l)}
    divisore = sqrt(sum(i)^2{t(i,j)-*mediat(j)} * sum(i){pmexpect_squared(i,l)} )
    */
    assert(numvalid <= BATCH_SIZE);
    TraceValueType tavg;
    // StatisticValueType dividendo;
    // StatisticValueType divisore;
    auto dividendi = shared_ptr<Matrix<StatisticValueType,1,KEYNUM> >(new Matrix<StatisticValueType,1,KEYNUM>() );
    auto divisori = shared_ptr<Matrix<StatisticValueType,1,KEYNUM> >(new Matrix<StatisticValueType,1,KEYNUM>() );
    for(unsigned long long time=0; time < numvalid; time++) {
        tavg = traces->col(time).array().sum() / traces->col(time).array().count();
        (*divisori) = ((traces->col(time).array() - tavg).matrix().squaredNorm() * pmexpect_bykey).array().sqrt();
        (*dividendi).noalias() = (traces->col(time).array() - tavg).matrix().transpose() * pmexpect;
        stat->row(time) = (*dividendi).array() / (*divisori).array();

    }
}


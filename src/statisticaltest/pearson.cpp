#include "dpacalc.h"
#include "pearson.hpp"
Statistic::pearson::pearson(shared_ptr< PowerModelMatrix >& _pm): base(_pm)
{
    Eigen::Matrix<TraceValueType,1,KEYNUM> pmaverage = Matrix<TraceValueType,1,KEYNUM> ();
    pm=shared_ptr<PowerModelMatrix> ( _pm );
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
    pmexpect_squared = pmexpect.array().square();

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
    StatisticValueType dividendo;
    StatisticValueType divisore;
    for(unsigned long long time=0; time < numvalid; time++) {
        tavg = traces->col (time).array().sum() / traces->col(time).array().count();
        for(unsigned long long keyh=0; keyh < KEYNUM; keyh++) {
//	    cout << "Computing Perarson coeff between " << traces->col(time).array() << " and " << pm->col(keyh).array() <<endl;
	    dividendo = (traces->col(time).array() - tavg).cwiseProduct(pmexpect.col(keyh).array()).sum();
            divisore=(traces->col(time).array() - tavg).square().sum() * pmexpect_squared.col(keyh).array().sum(); //here it can be optimized further. The second factor doesn't depend on time, so it can be precomputed in constructor.
	    divisore=sqrt(divisore);
            (*stat)(time,keyh)=dividendo/divisore;
//	    cout << " - Result: " << (*stat)(time,keyh) << endl;


        }
    }
}


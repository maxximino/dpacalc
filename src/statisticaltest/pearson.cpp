#include "dpacalc.h"
#include "pearson.hpp"

Statistic::pearson::pearson ( shared_ptr< PowerModelMatrix >& _pm,unsigned long long nt ) :base ( _pm,nt ),batches()
{
    pm=shared_ptr<PowerModelMatrix> ( _pm );
    pmaverage = Matrix<TraceValueType,Dynamic,1> ( pm->rows(),1 );
    for ( long d = 0; d < pm->rows(); d++ )
    {
        //sum overflow? si può fare approccio tipo ricerca binaria, ma efficienza cala.
        pmaverage ( d,0 ) = pm->row ( d ).array().sum() / pm->row ( d ).array().count();
    }
    cout << "Power Average: " <<endl <<pmaverage <<endl;
}

void Statistic::pearson::parallel_pass3 ( unsigned long long batchid )
{
    cout << "Passo 3 batch " << batchid <<endl;
}
void Statistic::pearson::sequential_printCSV ( unsigned long long batchid, ostream &out )
{

}
void Statistic::pearson::single_pass2()
{
    traceaverage = Matrix<TraceValueType,Dynamic,1> ( NumTraces,1 );

    for ( unsigned long long t = 0; t < NumTraces; t++ )
    {
        //sum overflow? si può fare approccio tipo ricerca binaria, ma efficienza cala.
        traceaverage ( t,0 ) = 0;
        TraceValueType coeffsum=0;
        for ( std::map<unsigned long long,shared_ptr<BatchInfo> >::iterator it = batches.begin(); it != batches.end(); ++it )
        {
            TraceValueType coeff = 1;
            if(it->second->numvalid != BATCH_SIZE) { //Only for the last one.
                coeff = (TraceValueType)it->second->numvalid/(TraceValueType)BATCH_SIZE;
            }
            cout << "old value " << traceaverage (t,0) << " coeff " << coeff << " added value " << it->second->blktraceaverage(t,0) << endl;
            traceaverage (t,0) += it->second->blktraceaverage(t,0) * coeff;
            cout << "new value " << traceaverage (t,0)  << endl;
            coeffsum +=coeff;
        }
        cout << "Trace sum:" <<traceaverage (t,0) << " size " << batches.size() << endl;
        traceaverage (t,0) /= coeffsum;
    }
    cout << "Traces average: " <<endl <<traceaverage <<endl;

}
void Statistic::pearson::parallel_pass1 ( unsigned long long batchid,shared_ptr<TracesMatrix> &traces,unsigned long numvalid )
{
    shared_ptr<BatchInfo> bi = shared_ptr<BatchInfo> ( new BatchInfo() );
    bi->numvalid=numvalid;
    bi->traces=shared_ptr<TracesMatrix> ( traces );
    pmaverage = Matrix<TraceValueType,Dynamic,1> ( traces->rows(),1 );
    for ( long d = 0; d < pm->rows(); d++ )
    {
        //sum overflow? si può fare approccio tipo ricerca binaria, ma efficienza cala.
        bi->blktraceaverage ( d,0 ) = traces->row ( d ).array().leftCols ( numvalid ).sum() / numvalid;
    }
    cout << "Chunk of traces average: " <<endl <<bi->blktraceaverage <<endl;
    batches.insert(pair <unsigned long long,shared_ptr<BatchInfo> >(batchid,shared_ptr<BatchInfo>(bi)));
}


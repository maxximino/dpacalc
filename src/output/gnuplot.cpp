#include "dpacalc.h"
#include "gnuplot.hpp"
#include <mutex>
#include <bits/stl_map.h>
using namespace std;
void Output::gnuplot::init()
{
    dataoutp.open(dataNameArg.getValue());
    if(!dataoutp.is_open()) {
        cerr << "Please provide a valid data output filename" <<endl;
        exit(1);
    }
    ofstream scriptoutp(scriptNameArg.getValue());
    if(!scriptoutp.is_open()) {
        cerr << "Please provide a valid script output filename" <<endl;
        exit(1);
    }
    scriptoutp << "set term png size 3000,1500 crop;" << endl;
    scriptoutp << "set output \"output.png\";" << endl;
    scriptoutp << "set autoscale;" << endl;
    scriptoutp << "set xtic auto;" << endl;
    scriptoutp << "set ytic auto;" << endl;
    scriptoutp << "set key outside right;" << endl;
    scriptoutp << "set title \"DPAcalc graphical output\";" << endl;
    scriptoutp << "set xlabel \"Time\";" << endl;
    scriptoutp << "set ylabel \"Pearson coefficient\";" << endl<< endl<< endl<< endl<< endl;
    scriptoutp << "plot ";
    for(unsigned long long k=0; k < KEYNUM; k++) {
        scriptoutp  << " \"" << dataNameArg.getValue() << "\" u 1:" << k+2 << " t \"" << keygen->getKeyAsString(k) << "\" with lines";
        if(k != KEYNUM-1) {
            scriptoutp  << ",";
        }
    }
    scriptoutp.close();
}
void Output::gnuplot::WriteBatch(unsigned long long id, shared_ptr< StatisticIndexMatrix >& s) {
    queueMutex.lock();
    //if(id==2)id=3;else if(id==3)id=2; // Ugly, destroys final output, but demonstrates the problem.
    if(id == doneId+1) {

        this->RealWriteBatch(id,s);
        doneId=id;
        this->emptyQueue();
    }
    else {
        cout << "in queue"<<endl;
        wqueue.insert(pair<unsigned long long,shared_ptr< StatisticIndexMatrix > >(id, shared_ptr<StatisticIndexMatrix>(s)));
    }
    queueMutex.unlock();
    //this is not designed to enhance output performance, but just to ensure output correctness. (batch with higher ID cannot write before previous batches)
}
void Output::gnuplot::emptyQueue()
{
    long id=doneId;
    while(wqueue.count(++id)) {
        this->RealWriteBatch(id,wqueue[id]);
        doneId=id;
        wqueue.erase(id);
    }
}

void Output::gnuplot::RealWriteBatch(unsigned long long id,shared_ptr< StatisticIndexMatrix >& s)
{
    //*s=s->cwiseAbs();
    //cout << "Writing batch " << id << endl;
    for(long long r=0; r < s->rows(); r++) {
        dataoutp << r ;
        for(long long c=0; c < s->cols(); c++) {
            dataoutp << "\t" << (*s)(r,c);
        }
        dataoutp << endl;
    }

}
void Output::gnuplot::end()
{
    Output::base::end();
    cout << "Fine con " << wqueue.size() << " elementi in coda" << endl;
}


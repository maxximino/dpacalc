#include "dpacalc.h"

#include "gnuplot.hpp"
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
    scriptoutp << "set title \"DPAcalc graphical output\";" << endl;
    scriptoutp << "set xlabel \"Time\";" << endl;
    scriptoutp << "set ylabel \"Pearson coefficient\";" << endl<< endl<< endl<< endl<< endl;
    scriptoutp << "plot ";
    for(unsigned long long k=0; k < KEYNUM; k++) {
        scriptoutp  << " \"" << dataNameArg.getValue() << "\" u 1:" << k+2 << " t \"Key " << k << "\" with lines";
        if(k != KEYNUM-1) {
            scriptoutp  << ",";
        }
    }
    scriptoutp.close();
}

void Output::gnuplot::WriteBatch(unsigned long long id, shared_ptr< StatisticIndexMatrix >& s)
{
  *s=s->cwiseAbs();
    for(long long r=0; r < s->rows(); r++) {
        dataoutp << r ;
        for(long long c=0; c < s->cols(); c++) {
            dataoutp << "\t" << (*s)(r,c);
        }
        dataoutp << endl;
    }

}

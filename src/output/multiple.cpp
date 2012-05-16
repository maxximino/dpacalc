#include "multiple.hpp"
#include "coarseresult.hpp"
#include "gnuplot.hpp"
Output::multiple::multiple(TCLAP::CmdLine& cmd, shared_ptr< KeyGenerators::base > _keygen):base(cmd,_keygen),outputs()
{
    outputs.push_back(shared_ptr<Output::base>(new Output::coarseresult(cmd,keygen)));
    outputs.push_back(shared_ptr<Output::base>(new Output::gnuplot(cmd,keygen)));
}
void Output::multiple::end()
{
    Output::base::end();
    for (vector<shared_ptr<Output::base> >::iterator it = outputs.begin(); it!=outputs.end(); ++it) {
        (*it)->end();
    }
}
void Output::multiple::init()
{
    Output::base::init();
    for (vector<shared_ptr<Output::base> >::iterator it = outputs.begin(); it!=outputs.end(); ++it) {
        (*it)->init();
    }
}
void Output::multiple::WriteBatch(long long unsigned int id, shared_ptr< StatisticIndexMatrix >& s)
{
    for (vector<shared_ptr<Output::base> >::iterator it = outputs.begin(); it!=outputs.end(); ++it) {
        (*it)->WriteBatch(id,s);
    }
}

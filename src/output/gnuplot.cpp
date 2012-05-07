#include "gnuplot.hpp"
void Output::gnuplot::init()
{

}

void Output::gnuplot::WriteBatch(unsigned long long id, shared_ptr< StatisticIndexMatrix >& s)
{
cout << *s;
}

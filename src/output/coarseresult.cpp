#include "coarseresult.hpp"
void Output::coarseresult::end(){
  cout << "The best key hypotesis is: " << keygen->getKeyAsString(best) <<endl;
  cout << "and its statistic index is: " << bestval <<endl;
}
void Output::coarseresult::WriteBatch(unsigned long long id,shared_ptr<StatisticIndexMatrix> &s){
    StatisticIndexMatrix::Index maxRow, maxCol;
  (*s)=s->cwiseAbs();
  StatisticValueType max = s->maxCoeff(&maxRow, &maxCol);
  checkingMutex.lock();
  if(max > bestval){
    bestval=max;
    best=maxCol;
  }
  checkingMutex.unlock();
}
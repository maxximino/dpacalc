#include "cxx11threads.hpp"
#include <thread>
#include "main.hpp"
    void threadfunction();
    unsigned long batchmax=0;
    unsigned long batchcur=0;
    mutex cur_mutex;
void ExecMethod::cxx11threads::RunAndWait(unsigned long numberoftimes)
{
  batchmax=numberoftimes;
  batchcur=0;
  int numCPU = sysconf( _SC_NPROCESSORS_ONLN );
  vector<thread> thrs;
  for(int i = 0; i<numCPU;i++){
    thrs.push_back(thread(threadfunction));
  }
  for (auto t = thrs.begin(); t != thrs.end(); ++t) {
    t->join();
  }
  
}

 void threadfunction()
{
  for(;;){
  cur_mutex.lock();
  if(batchcur < batchmax){
    ++batchcur;
  }
  else{
    cur_mutex.unlock();
      break;
  }
  cur_mutex.unlock();
  DPA::instance()->doRun();
  }
}
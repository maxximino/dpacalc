#include "bbque.hpp"
#include "main.hpp"
void prefetchthread();
void threadfunction();

void ExecMethod::bbque::RunAndWait(unsigned long numberoftimes)
{
  std::thread prefetcht = thread(prefetchthread);
  RTLIB_Services_t *rtlib;
  RTLIB_Init("DPAcalc", &rtlib);
  assert(rtlib);
  shared_ptr<ExecMethod::BbqueClass> bc = shared_ptr<ExecMethod::BbqueClass>(new ExecMethod::BbqueClass("DPAcalc","DPAcalcRecipe",rtlib,numberoftimes));
  assert(bc->isRegistered());
  bc->Start();
  bc->WaitCompletion();
  prefetcht.join();
  //la distruzione avviene con la fine di questo metodo (grazie inventore dello shared_ptr!).
}

ExecMethod::BbqueClass::BbqueClass(const string& name, const string& recipe, RTLIB_Services_t* rtlib,unsigned long _tot):BbqueEXC(name, recipe, rtlib),mtx()
{
  tot=_tot;
  num=0;
cout << "BbqueClass initialized."<<endl;
}
RTLIB_ExitCode_t ExecMethod::BbqueClass::onConfigure(uint8_t awm_id)
{
return RTLIB_OK;
}
RTLIB_ExitCode_t ExecMethod::BbqueClass::onMonitor()
{
return RTLIB_OK;
}
RTLIB_ExitCode_t ExecMethod::BbqueClass::onRun()
{
  int numCPU= sysconf( _SC_NPROCESSORS_ONLN ); // So che non è il metodo corretto.
 unsigned int oldnum;
  mtx.lock();
  
  if(num >= tot){
    mtx.unlock();
    return RTLIB_EXC_WORKLOAD_NONE;
  }
  oldnum=num;
    vector<thread> thrs;
    for(; num<oldnum+numCPU; num++) {
	if(num >= tot){
	  break;
	}
        thrs.push_back(thread(threadfunction));
    }
    mtx.unlock();
    for (auto t = thrs.begin(); t != thrs.end(); ++t) {
        t->join();
    }

 return RTLIB_OK;
}
RTLIB_ExitCode_t ExecMethod::BbqueClass::onSetup()
{
return RTLIB_OK;
}

void prefetchthread() {
    DPA::instance()->prefetch();
}

void threadfunction()
{
        DPA::instance()->doRun();
}

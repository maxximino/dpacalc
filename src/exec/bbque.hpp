#pragma once
#include "dpacalc.h"
#include "base.hpp"
#include <mutex>
#include <bbque/bbque_exc.h>

using bbque::rtlib::BbqueEXC;

namespace ExecMethod {
class bbque: public base {
public:
    bbque(TCLAP::CmdLine& cmd):base(cmd) {}
    virtual void RunAndWait(unsigned long numberoftimes);  //What should I run? DPA::onRun(); called on the right thread.
};
class BbqueClass: public BbqueEXC{
public:	
      BbqueClass(std::string const & name,
			std::string const & recipe,
			RTLIB_Services_t *rtlib,unsigned long _tot);
protected:
	unsigned long tot;
	unsigned long num;
 	std::mutex mtx;
  	RTLIB_ExitCode_t onSetup();
	RTLIB_ExitCode_t onConfigure(uint8_t awm_id);
	RTLIB_ExitCode_t onRun();
	RTLIB_ExitCode_t onMonitor();
  
};
}


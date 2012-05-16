#pragma once
#include "dpacalc.h"
#include "base.hpp"

namespace ExecMethod
{
	class cxx11threads: public base
	{
		public:
			cxx11threads ( TCLAP::CmdLine& cmd ) : base ( cmd ), procArg ( "p", "processors", "Number of processors to use (0=autodetect)", false, 0, "int" ) {
				cmd.add ( procArg );
			};
			virtual void RunAndWait ( unsigned long numberoftimes );
		protected:
			TCLAP::ValueArg<int> procArg;
	};
}
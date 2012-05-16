#pragma once
#include "dpacalc.h"
#include "base.hpp"
#include <fstream>
#include <map>
#include <mutex>
using namespace std;
namespace Output
{
	class gnuplot: public base
	{
		public:
			gnuplot ( TCLAP::CmdLine& cmd, shared_ptr<KeyGenerators::base> _keygen ) : base ( cmd, _keygen ),
				dataNameArg ( "o", "output", "Gnuplot data file name", true, "", "path" ),
				scriptNameArg ( "s", "script-output", "Gnuplot script output file name", true, "", "path" ), wqueue(), queueMutex() {
				doneId = -1;
				cmd.add ( dataNameArg );
				cmd.add ( scriptNameArg );
			};
			virtual void init();
			virtual void end();
			virtual void WriteBatch ( unsigned long long id, shared_ptr<StatisticIndexMatrix>& s );
		protected:
			TCLAP::ValueArg<std::string> dataNameArg;
			TCLAP::ValueArg<std::string> scriptNameArg;
			std::ofstream dataoutp;
			unsigned long long doneId;
			std::map<unsigned long long, shared_ptr<StatisticIndexMatrix>> wqueue;
			std::mutex queueMutex;
			virtual void RealWriteBatch ( unsigned long long id, shared_ptr<StatisticIndexMatrix>& s );
			virtual void emptyQueue();
	};

}

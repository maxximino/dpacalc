#pragma once
#include "dpacalc.h"
#include "base.hpp"
#include <fstream>
#include <map>
#include <mutex>
using namespace std;
namespace Output
{
	class coarseresult: public base
	{
		public:
			coarseresult ( TCLAP::CmdLine& cmd, shared_ptr<KeyGenerators::base> _keygen ) : base ( cmd, _keygen ), checkingMutex() {
				best = 0;
				bestval = -1;
			};
			virtual void end();
			virtual void WriteBatch ( unsigned long long id, shared_ptr<StatisticIndexMatrix>& s );
		protected:
			KeyIndexType best;
			StatisticValueType bestval;
			std::mutex checkingMutex;
	};

}

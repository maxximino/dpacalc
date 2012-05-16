#pragma once
#include "dpacalc.h"
using namespace Eigen;
using namespace std;
namespace Statistic
{
	class base
	{
		public:
			virtual void generate ( shared_ptr<StatisticIndexMatrix>& stat, shared_ptr<TracesMatrix>& traces, unsigned long numvalid ) = 0;
			base ( TCLAP::CmdLine& cmd ) {};
			virtual void init ( shared_ptr<PowerModelMatrix>& _pm ) {
				pm = shared_ptr<PowerModelMatrix> ( _pm );
			}
		protected:
			shared_ptr<PowerModelMatrix> pm;
	};
}

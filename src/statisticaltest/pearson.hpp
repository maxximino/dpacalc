#pragma once
#include "dpacalc.h"
#include "base.hpp"
#include <map>
using namespace Eigen;
using namespace std;
namespace Statistic
{
	class pearson : public base
	{
		public:
			virtual void generate ( shared_ptr<StatisticIndexMatrix>& stat, shared_ptr<TracesMatrix>& traces, unsigned long numvalid );
			pearson ( TCLAP::CmdLine& cmd ) : base ( cmd ) {};
			virtual void init ( shared_ptr<PowerModelMatrix>& _pm );
		protected:
			Eigen::Matrix<TraceValueType, Dynamic, Dynamic> pmexpect;
			Eigen::Matrix<TraceValueType, 1, Dynamic> pmexpect_bykey;
	};
}


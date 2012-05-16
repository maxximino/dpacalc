#pragma once
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace GeneratePowerModel
{
	class pm1 : public base
	{
		public:
			virtual void generate ( shared_ptr<IntermediateValueMatrix>& intval, shared_ptr<PowerModelMatrix>& pm );
			pm1 ( TCLAP::CmdLine& cmd ) : base ( cmd ) {}
	};
}


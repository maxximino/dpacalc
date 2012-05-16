#pragma once
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace GeneratePowerModel
{
	class hammingweight : public base
	{
		public:
			virtual void generate ( shared_ptr<IntermediateValueMatrix>& intval, shared_ptr<PowerModelMatrix>& pm );
			hammingweight ( TCLAP::CmdLine& cmd ) : base ( cmd ) {}
	};
}


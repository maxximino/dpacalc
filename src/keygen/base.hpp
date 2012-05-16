#pragma once
#include "dpacalc.h"
#include <bitset>
#include <iostream>
namespace KeyGenerators
{
	class base
	{
		public:
			base ( TCLAP::CmdLine& cmd ) {};
			virtual void init() {};
			virtual  KeyDataType getKeyFromIndex ( KeyIndexType idx ) = 0;
			virtual std::string getKeyAsString ( KeyIndexType idx ) {
				std::stringstream s;
				s << std::hex;
				s << idx;
				return s.str();
			};
	};
}

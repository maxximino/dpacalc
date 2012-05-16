#pragma once
#include "base.hpp"
#include "dpacalc.h"
#include <bitset>
#include <iostream>
namespace KeyGenerators
{
	class aes128keygen: public base
	{
		public:
			aes128keygen ( TCLAP::CmdLine& cmd ) : base ( cmd ), shiftbitsArgs ( "k", "shiftkey", "Shift key hypotesis bits on the left by X bits", false, 0, "int" ) {
				cmd.add ( shiftbitsArgs );
			};
			virtual void init();
			virtual KeyDataType getKeyFromIndex ( KeyIndexType idx ) ;

		protected:
			TCLAP::ValueArg<int> shiftbitsArgs;
	};
}

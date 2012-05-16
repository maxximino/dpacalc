#include "dpacalc.h"
#include "pm1.hpp"
void GeneratePowerModel::pm1::generate ( shared_ptr<IntermediateValueMatrix>& intval, shared_ptr<PowerModelMatrix>& pm )
{
	std::bitset<sizeof ( IntermediateValueType ) *8> tmp;
	IntermediateValueType value;
	for ( long long d = 0; d < pm->rows(); d++ ) {
		for ( unsigned long long k = 0; k < KEYNUM; k++ ) {
			value = ( *intval ) ( d, k );
			BufferToBitset<sizeof ( IntermediateValueType ) > ( ( char* ) &value, tmp );
			( *pm ) ( d, k ) = tmp.count();
		}
	}
}

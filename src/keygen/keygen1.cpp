#include "keygen1.hpp"
#include <iostream>
using namespace std;
KeyDataType KeyGenerators::keygen1::getKeyFromIndex ( KeyIndexType idx )
{
	assert ( idx < KEYNUM );
	std::bitset<KEY_SIZE_BIT> key = std::bitset<KEY_SIZE_BIT> ( idx );
	key <<= shiftbitsArgs.getValue();
	//This can be useful for debugging of understanding how it works
	//std::cout << "Key after shifting:" << key << std::endl;
	return key;
}

void KeyGenerators::keygen1::init()
{
	if ( shiftbitsArgs.getValue() > ( KEY_SIZE_BIT - KEY_HYP_BIT ) || shiftbitsArgs.getValue() < 0 ) {
		std::cerr << "You cannot shift more than " << ( KEY_SIZE_BIT - KEY_HYP_BIT ) << " bits because you're guessing " << KEY_HYP_BIT << "bits out of " << KEY_SIZE_BIT << std::endl;
		exit ( 1 );
	}
}


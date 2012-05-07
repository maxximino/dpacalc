#include "dpacalc.h"
#include "int1.hpp"
#include "aes.h"

void BufferToBitset(char *buffer,std::bitset<DATA_SIZE_BIT> &bitset);
void BitsetToBuffer(std::bitset<DATA_SIZE_BIT> &bitset,char *buffer) {
    
    for(unsigned long dim = 0; dim < DATA_SIZE_BYTE; dim++) {
        if(dim>0) {
            bitset <<= 8;
        }
        *buffer = 0;
	if(bitset.test(0)) (*buffer) = (*buffer) |1;
	if(bitset.test(1)) (*buffer) = (*buffer) |2;
	if(bitset.test(2)) (*buffer) = (*buffer) |4;
	if(bitset.test(3)) (*buffer) = (*buffer) |8;
	if(bitset.test(4)) (*buffer) = (*buffer) |16;
	if(bitset.test(5)) (*buffer) = (*buffer) |32;
	if(bitset.test(6)) (*buffer) = (*buffer) |64;
	if(bitset.test(7)) (*buffer) = (*buffer) |128;
         buffer++;
    }

}
void GenerateIntermediateValues::int1::generate(shared_ptr<DataMatrix> &knowndata,shared_ptr<IntermediateValueMatrix> &intval)
{
      uint8_t fullaeskey[AES_STATE_BYTES_NO];
      uint8_t fullaesdata[AES_STATE_BYTES_NO];
      memset(fullaeskey,0,AES_STATE_BYTES_NO);

      /*AddRoundKey(OutValue,UnrolledRoundKey[0]);

	for (i=1;i<=10;i++)
	{
		SubBytes(OutValue);
	*/	
      std::bitset<DATA_SIZE_BIT> tmpdata;
      unsigned long long* fullaeskey_ptr = (unsigned long long*)fullaeskey;
    for(unsigned long trcidx = 0; trcidx < knowndata->size(); trcidx++) {
        for(KeyIndexType keyidx=0; keyidx < KEYNUM ; ++keyidx) {
	  BitsetToBuffer((*knowndata)[trcidx],(char*)&fullaesdata);
	  *(fullaeskey_ptr)=keygen->getKeyFromIndex(keyidx); //Last 64 bit always at zero. Endianness problem.
	  AddRoundKey(fullaesdata,fullaeskey);
	  SubBytes(fullaesdata);
	  BufferToBitset((char*)fullaesdata,tmpdata);
        (*intval)[trcidx][keyidx] = tmpdata;
       
        }
    }
}


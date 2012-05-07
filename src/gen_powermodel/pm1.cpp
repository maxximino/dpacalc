#include "dpacalc.h"
#include "pm1.hpp"
void GeneratePowerModel::pm1::generate(shared_ptr<IntermediateValueMatrix> &intval,shared_ptr<PowerModelMatrix> &pm)
{
    for(long long d = 0; d < pm->rows();d++){
      for(unsigned long long k = 0; k < KEYNUM;k++){
    
	(*pm)(d,k) = (*intval)[d][k].count();
    }
     }
     cout << "---------- PM ------------------- " <<endl << *pm << endl << "---------------------------------------" << endl;
}

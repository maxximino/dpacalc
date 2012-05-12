#include "seq_monocore.hpp"
#include "main.hpp"

void ExecMethod::seq_monocore::RunAndWait(unsigned long numberoftimes)
{
    DPA* inst = DPA::instance();
    for(unsigned long n = 0; n < numberoftimes; n++) {
        inst->doRun();
    }
}

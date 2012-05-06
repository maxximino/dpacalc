#pragma once
#include "dpacalc.h"
#include <mutex>
using namespace Eigen;
using namespace std;

class DPA {
public:

    int main(int argc,char**argv);
    void doRun();
    void prefetch();
    static DPA* instance() {
        static DPA theInstance;
        return &theInstance;
    }
protected:
    shared_ptr<DataMatrix> data;
    shared_ptr<IntermediateValueMatrix> intval;
    shared_ptr<PowerModelMatrix> pm;
    shared_ptr<StatisticIndexMatrix> sm;
    unsigned long numbatches;
    shared_ptr<SamplesInput::base> input;
    shared_ptr<Statistic::base> stat;
    shared_ptr<KeyGenerators::KEYGENCLASS> keygen;
    shared_ptr<GenerateIntermediateValues::base> interm;
    shared_ptr<GeneratePowerModel::base> genpm;
    shared_ptr<ExecMethod::base> exec;
private:
    DPA() {}
};

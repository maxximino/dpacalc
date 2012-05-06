#include "dpacalc.h"
#include "statisticaltest/base.hpp"
#include <iostream>
#include <fstream>
#include "main.hpp"
#include <sys/time.h>
#define VERSION "0.01alpha"
using namespace Eigen;
using namespace std;

void DPA::doRun() //BBQ-style. This method can be started multiple times in different threads. Elaborates BATCH_SIZE time samples, for each possible key value.
{
    unsigned long long myid;
    shared_ptr<TracesMatrix> traces;
    shared_ptr<StatisticIndexMatrix> sm;
    int num = input->read(&myid,&traces);
    //cout << "Ho " << num << " sample validi. Tracce:" <<endl << *traces << endl;
    sm.reset(new StatisticIndexMatrix(num,KEYNUM));
    stat->generate(sm,traces,num);
}
long timevaldiff(struct timeval *starttime, struct timeval *finishtime)
{
    long msec;
    msec=(finishtime->tv_sec-starttime->tv_sec)*1000;
    msec+=(finishtime->tv_usec-starttime->tv_usec)/1000;
    return msec;
}

void DPA::prefetch() {
    while(input->CurrentSample < input->SamplesPerTrace) {
        input->populateQueue();
    }
}

int DPA::main(int argc, char** argv)
{
    TCLAP::CmdLine cmd("DPA calc", ' ', VERSION);

    exec = shared_ptr<ExecMethod::base>(new ExecMethod::EXECCLASS(cmd));
    input = shared_ptr<SamplesInput::base>(new SamplesInput::INPUTCLASS(cmd));
    keygen= shared_ptr<KeyGenerators::KEYGENCLASS>(new KeyGenerators::KEYGENCLASS(cmd));
    interm= shared_ptr<GenerateIntermediateValues::base>(new GenerateIntermediateValues::GENINTERMCLASS(cmd,keygen));
    genpm= shared_ptr<GeneratePowerModel::base>(new GeneratePowerModel::GENPOWERMODELCLASS(cmd));
    stat = shared_ptr<Statistic::base>(new Statistic::STATISTICCLASS(cmd));
    try {
        cmd.parse( argc, argv );

    } catch (TCLAP::ArgException &e)
    {
        cerr << "Error " << e.error() << " in command line argument " << e.argId() << std::endl;
        return 1;
    }
    // Get the value parsed by each arg.
    input->init();
    timeval start,end;
    gettimeofday(&start,NULL);
    keygen->init();
    interm->init();
    genpm->init();
    numbatches= (input->SamplesPerTrace/BATCH_SIZE) + (((input->SamplesPerTrace%BATCH_SIZE)==0)?0:1);
    cout << "Reading known data..." <<endl;
    data = input->readData();
    cout << "Done. Calculating intermediate values.....[single threaded]" <<endl;

    intval.reset( new IntermediateValueMatrix(input->NumTraces,KEYNUM));
    interm->generate(data,intval);
    data.reset(); // I don't need that data anymore.
    // cout << "Valori intermedi: " <<  endl<<*intval <<endl;
    cout << "Done. Calculating power model.....[single threaded]" <<endl;

    pm.reset(new PowerModelMatrix(input->NumTraces,KEYNUM));
    genpm->generate(intval,pm);
    intval.reset(); // I don't need that data anymore, let's free some memory!
    // cout << "modello del consumo di potenza: " <<  endl<<*pm <<endl;
    cout << "Done. Initializing statistic test [single threaded]:" <<endl;
    // StatisticIndexMatrix size should be a multiple of BATCH_SIZE
    unsigned long sz = input->SamplesPerTrace;
    if(sz % BATCH_SIZE > 0) sz += (BATCH_SIZE - (sz % BATCH_SIZE)) ;
    stat->init(pm);
    cout << "Done. Starting statistic test pass 1 [multithreaded]" <<endl;
    exec->RunAndWait(numbatches);
    gettimeofday(&end,NULL);

    printf ("Elaboration took %li milliseconds.\n", timevaldiff(&start,&end));

    //cout << "Done. Result:" <<endl << *sm <<endl;
    return 0;

}

int main(int argc,char**argv)
{
    DPA* me = DPA::instance();
    return me->main(argc,argv);

}
#include "dpacalc.h"
#include <iostream>
#include <fstream>
#include <tclap/CmdLine.h>
#include <mutex>
#define VERSION "0.01alpha"
using namespace Eigen;
using namespace std;

class DPA {

public:
    DPA():nextbatch_mutex() {

    }
    int main(int argc,char**argv) {
        TCLAP::CmdLine cmd("DPA calc", ' ', VERSION);
        TCLAP::ValueArg<std::string> nameArg("f","filename","Input file name",true,"","string");

        try {
            cmd.add( nameArg );
            cmd.parse( argc, argv );

        } catch (TCLAP::ArgException &e)
        {
            cerr << "Error " << e.error() << " in command line argument " << e.argId() << std::endl;
            return 1;
        }
        // Get the value parsed by each arg.
        shared_ptr<ifstream> inputfile(new ifstream(nameArg.getValue()));
        if(!(*inputfile)) {
            cerr << "Cannot open "<< nameArg.getValue() << endl;
            return 1;
        }
        input = shared_ptr<SamplesInput::base>(new SamplesInput::INPUTCLASS(inputfile));
        keygen= shared_ptr<KeyGenerators::KEYGENCLASS>(new KeyGenerators::KEYGENCLASS());
        interm= shared_ptr<GenerateIntermediateValues::base>(new GenerateIntermediateValues::GENINTERMCLASS(keygen));
        genpm= shared_ptr<GeneratePowerModel::base>(new GeneratePowerModel::GENPOWERMODELCLASS());

        numbatches= (input->SamplesPerTrace/BATCH_SIZE) + (((input->SamplesPerTrace%BATCH_SIZE)==0)?0:1);
        cout << "Reading known data..." <<endl;
        data = input->readData();
        cout << "Dati delle tracce:";
        for(unsigned int i = 0; i < data->capacity(); i++) {
            cout << (*data)[i] << endl;
        }
        cout << "Done. Calculating intermediate values.....[single threaded]" <<endl;

        intval.reset( new IntermediateValueMatrix(input->NumTraces,KEYNUM));
        interm->generate(data,intval);
        data.reset(); // I don't need that data anymore.
        cout << "Valori intermedi: " <<  endl<<*intval <<endl;
        cout << "Done. Calculating power model.....[single threaded]" <<endl;

        pm.reset(new PowerModelMatrix(input->NumTraces,KEYNUM));
        genpm->generate(intval,pm);
        intval.reset(); // I don't need that data anymore, let's free some memory!
        cout << "modello del consumo di potenza: " <<  endl<<*pm <<endl;
        cout << "Done. Starting statistic test pass 1 [multithreaded]" <<endl;
        stat = shared_ptr<Statistic::base>(new Statistic::STATISTICCLASS(pm,input->NumTraces));
        for(unsigned long i = 0; i<numbatches; i++) { //most stupid sequential mono-core executor
            doRun();
        }
        stat->single_pass2();
        nextbatch=0;
        for(unsigned long i = 0; i<numbatches; i++) { //most stupid sequential mono-core executor
            doRun2();
        }

        return 0;
    };
    void doRun2() {
        nextbatch_mutex.lock();
        unsigned long myid = nextbatch;
        nextbatch++;
        nextbatch_mutex.unlock();
        if(nextbatch > numbatches) {
            return;
        }
        stat->parallel_pass3(myid);
    }
    void doRun() { //BBQ-style. This method can be started multiple times in different threads. Elaborates BATCH_SIZE time samples, for each possible key value.
        unsigned long long myid;
        shared_ptr<TracesMatrix> traces;
        int num = input->read(BATCH_SIZE,&myid,&traces);
        cout << "Ho " << num << " sample validi. Tracce:" <<endl << *traces << endl;
        stat->parallel_pass1(myid,traces,num);

    }
protected:
    shared_ptr<DataMatrix> data;
    shared_ptr<IntermediateValueMatrix> intval;
    shared_ptr<PowerModelMatrix> pm;
    unsigned long numbatches;
    shared_ptr<SamplesInput::base> input;
    shared_ptr<Statistic::base> stat;
    shared_ptr<KeyGenerators::KEYGENCLASS> keygen;
    shared_ptr<GenerateIntermediateValues::base> interm;
    shared_ptr<GeneratePowerModel::base> genpm;
    unsigned long nextbatch ;
    std::mutex nextbatch_mutex;
};
int main(int argc,char**argv)
{
    DPA me;
    return me.main(argc,argv);

}

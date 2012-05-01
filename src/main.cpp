#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <tclap/CmdLine.h>
#include "config.h"
#include <memory>
#include "input/bin1.hpp"
#include "keygen/keygen1.hpp"
#include "gen_intermediate/int1.hpp"
#include "gen_powermodel/pm1.hpp"
#define VERSION "0.01alpha"
using namespace Eigen;
using namespace std;

class DPA {

public:
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
        ifstream inputfile(nameArg.getValue());
        if(!inputfile) {
            cerr << "Cannot open "<< nameArg.getValue() << endl;
            return 1;
        }
        input = shared_ptr<SamplesInput::base>(new SamplesInput::INPUTCLASS(&inputfile));
        keygen= shared_ptr<KeyGenerators::KEYGENCLASS>(new KeyGenerators::KEYGENCLASS());
        interm= shared_ptr<GenerateIntermediateValues::base>(new GenerateIntermediateValues::GENINTERMCLASS(keygen));
        genpm= shared_ptr<GeneratePowerModel::base>(new GeneratePowerModel::GENPOWERMODELCLASS());
        while(input->CurrentNumber < input->TotalNumber) { //most stupid sequential mono-core executor
            doRun();
        }
        return 0;
    };
    void doRun() { //BBQ-style. This method can be started multiple times in different threads. Elaborates BATCH_SIZE time samples, for each possible key value.
        unsigned long long myid;
        shared_ptr<TracesMatrix> traces = shared_ptr<TracesMatrix>( new TracesMatrix(BATCH_SIZE,input->TraceSize));
        shared_ptr<DataMatrix> data = shared_ptr<DataMatrix>( new DataMatrix());
        shared_ptr<IntermediateValueMatrix> intval;
        shared_ptr<PowerModelMatrix> pm;
        int num = input->read(BATCH_SIZE,&myid,traces,data);
        cout << "Ho " << num << " dati validi. Tracce:" <<endl << *traces << endl << "Dati: " <<endl << *data <<endl;
        intval.reset( new IntermediateValueMatrix());
        interm->generate(data,intval);
        data.reset(); // I don't need that data anymore, let's free some memory!
        cout << "Valori intermedi: " <<  endl<<*intval <<endl;
        pm.reset(new PowerModelMatrix());
        genpm->generate(intval,pm);
        intval.reset(); // I don't need that data anymore, let's free some memory!
        cout << "modello del consumo di potenza: " <<  endl<<*pm <<endl;

    }
protected:
    shared_ptr<SamplesInput::base> input;
    shared_ptr<KeyGenerators::KEYGENCLASS> keygen;
    shared_ptr<GenerateIntermediateValues::base> interm;
    shared_ptr<GeneratePowerModel::base> genpm;
};
int main(int argc,char**argv)
{
    DPA me;
    return me.main(argc,argv);

}

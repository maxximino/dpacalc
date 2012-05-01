#include "bin1.hpp"
#include <mutex>
//Here we can implement some sort of disk prefetching.
unsigned long long SamplesInput::bin1::read(unsigned long long num,unsigned long long *id, shared_ptr<Matrix<TRACETYPE,BATCH_SIZE,Dynamic> >traces, shared_ptr<Matrix<DATATYPE,BATCH_SIZE,1> > knowndata) {
    input_mutex.lock();
    if(CurrentNumber >= TotalNumber) {
        input_mutex.unlock();
        return 0;
    }
    if(num > (TotalNumber - CurrentNumber)) {
        num=(TotalNumber-CurrentNumber);
    }

    ++CurrentId;
    *id=CurrentId;

    //Read from file
    CurrentNumber += num;
    input_mutex.unlock();
    // Elaborate data and write into destination
    (*traces)(0,0)=1;
    (*traces)(0,1)=2;
    (*traces)(0,2)=3;
    (*traces)(1,0)=1;
    (*traces)(1,1)=4;
    (*traces)(1,2)=8;
    (*knowndata)(0,0)=100;
    (*knowndata)(1,0)=101;
    (*knowndata)(2,0)=102;
    return num;
}
SamplesInput::bin1::bin1(istream *_input):
    base(_input)
{
    TotalNumber= 10;
    TraceSize=100;
    cout<<"Costruttore di bin1"<<endl;
}


#pragma once
#include "dpacalc.h"
#include <iostream>
#include "base.hpp"
using namespace Eigen;
using namespace std;
namespace SamplesInput {
#pragma pack(push)
#pragma pack(1)
struct fileheaders {
    uint32_t numtraces;
    uint32_t numsamples_per_trace;
    char datatype;
    uint8_t knowndatalength;
};
#pragma pack(pop)

class bin1 : public base {
public:
    virtual unsigned long long read(unsigned long long num,unsigned long long *id, shared_ptr<TracesMatrix> *traces);
    bin1(shared_ptr<istream> _input);
    shared_ptr<DataMatrix> readData();
protected:
    template <class T> void readSamples(shared_ptr<TracesMatrix> &traces,unsigned long column, unsigned long numsamples);
    char sampletype;
    int samplesize;
    shared_ptr<DataMatrix> data;

    unsigned long long getSampleOffset(unsigned long long trace, unsigned long long samplenum) {
        //trace and samplenum are zero-based
        return sizeof(struct fileheaders) + trace*(samplesize*SamplesPerTrace + DATA_SIZE_BYTE) + samplesize*samplenum;
    }
    unsigned long long getDataOffset(unsigned long long trace) {
        //trace and samplenum are zero-based
        return sizeof(struct fileheaders) + trace*(samplesize*SamplesPerTrace + DATA_SIZE_BYTE) + samplesize*SamplesPerTrace;
    }
};
}
void BufferToBitset(char *buffer,std::bitset<DATA_SIZE_BIT> &bitset);
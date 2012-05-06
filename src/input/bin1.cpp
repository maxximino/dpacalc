#include "bin1.hpp"
#include <algorithm>
//Here we can implement some sort of disk prefetching.
long long unsigned int SamplesInput::bin1::read(long long unsigned int num, long long unsigned int* id, shared_ptr< TracesMatrix >* traces)
{
    unsigned long long cur_trace;
    input_mutex.lock();
    if(CurrentSample >= SamplesPerTrace) {
        input_mutex.unlock();
        return 0;
    }
    num = min<unsigned long long>(num,SamplesPerTrace-CurrentSample);
  //  cout << "I'm going to allocate a " << NumTraces << " * " << BATCH_SIZE << " * " << sizeof(TraceValueType) << " = " << (NumTraces*BATCH_SIZE*sizeof(TraceValueType)/1024) << " kb matrix"<<endl;
   
    traces->reset(new TracesMatrix(NumTraces,BATCH_SIZE));
    ++CurrentId;
    *id=CurrentId;
    for(cur_trace=0; cur_trace<NumTraces; cur_trace++) {
        input->seekg(getSampleOffset(cur_trace,CurrentSample),ios::beg);
        switch(sampletype) {
        case 'b':
            readSamples<uint8_t>(*traces,cur_trace,num);
            break;
        case 'c':
            readSamples<uint16_t>(*traces,cur_trace,num);
            break;
        case 'f':
            readSamples<float>(*traces,cur_trace,num);
            break;
        case 'd':
            readSamples<double>(*traces,cur_trace,num);
            break;
        }
    }
    CurrentSample+= num;
    input_mutex.unlock();
    return num;
}
template <class T>void SamplesInput::bin1::readSamples(shared_ptr<TracesMatrix> &traces,unsigned long column, unsigned long numsamples)
{
    T buffer[numsamples];
    input->read((char*)(&buffer),sizeof(T)*numsamples);
//File is big enough, checked right after open.
    for(unsigned long i = 0; i <numsamples; i++) {
        (*traces)(column,i) = buffer[i];
    }
}
void BufferToBitset(char *buffer,std::bitset<DATA_SIZE_BIT> &bitset) {
    for(unsigned long dim = 0; dim < DATA_SIZE_BYTE; dim++) {
        if(dim>0) {
            bitset <<= 8;
        }
        bitset |= *buffer;
        buffer++;
    }

}

std::shared_ptr< DataMatrix > SamplesInput::bin1::readData()
{
    char buf[DATA_SIZE_BYTE];
    if(data.get() != NULL) {
        return shared_ptr<DataMatrix>(data);
    }
    input_mutex.lock();
    data.reset( new DataMatrix(NumTraces));
    for(unsigned long cur_trace=0; cur_trace<NumTraces; cur_trace++) {
        input->seekg(getDataOffset(cur_trace),ios::beg);
        input->read(buf,DATA_SIZE_BYTE);
        BufferToBitset((char*)&buf,(*data)[cur_trace]);
    }
    input_mutex.unlock();
    return shared_ptr<DataMatrix>(data);

}
SamplesInput::bin1::bin1(shared_ptr<istream> _input):
    base(_input)
{
    struct fileheaders header;
    long long TotalFileSize;
    input->read((char*)(&header),sizeof(header));
    cout << "char:" << header.datatype <<endl;
    SamplesPerTrace=header.numsamples_per_trace;
    NumTraces=header.numtraces;
    switch(header.datatype) {
    case 'b':
        samplesize=1;
        sampletype='b';
        break;
    case 'c':
        samplesize=2;
        sampletype='c';
        break;
    case 'f':
        samplesize=4;
        sampletype='f';
        break;
    case 'd':
        samplesize=8;
        sampletype='d';
        break;
    default:
        cerr << "Sample data type should be b,c,f, or d. " << endl;
        exit(1);
    }
    TotalFileSize=sizeof(header) + header.numtraces*(header.knowndatalength+samplesize*header.numsamples_per_trace);
  
    input->seekg(0,ios::end);
    if(input->tellg()!=TotalFileSize) {
        cerr << "File size should be " << TotalFileSize << " but it is " << input->tellg() << endl <<" Header size: " << sizeof(header) << endl << header.numtraces <<" traces, single trace size: " << (int)header.knowndatalength << " (known data) + " << header.numsamples_per_trace << "*" << samplesize << " bytes." <<endl;
        exit(2);
    }
    if(header.knowndatalength != DATA_SIZE_BYTE) {
        cerr << "The length of each known data should be " << DATA_SIZE_BYTE << " but it is " << (int)header.knowndatalength << ". Change data file or recompile this program with appropriate options." <<endl;
        exit(2);
    }
    readData();
}


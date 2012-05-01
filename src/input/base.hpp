#include <iostream>
#include <Eigen/Dense>
#include <mutex>
#include <memory>

#include "config.h"
using namespace Eigen;
using namespace std;
namespace SamplesInput {
class base {
public:
    unsigned long long TotalNumber;  //dimension N of matrix T
    unsigned long long TraceSize; //dimension M of matrix T
    unsigned long long CurrentNumber;  //dimension N of matrix T
    base(istream *_input) {
        assert(_input != NULL);
        input=_input;
        CurrentNumber=0;
        CurrentId=-1;
    }

    virtual unsigned long long read(unsigned long long num,unsigned long long *id, shared_ptr<TracesMatrix>traces, shared_ptr<DataMatrix> knowndata) = 0;

protected:
    istream *input;
    unsigned long long CurrentId;
    std::mutex input_mutex;
};
}

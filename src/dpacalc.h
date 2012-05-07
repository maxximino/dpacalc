#pragma once
#include <Eigen/Dense>
#include <bitset>
#include <memory>
#include <tclap/CmdLine.h>
#include "config.h"
#include <boost/multi_array.hpp>

typedef std::bitset<DATA_SIZE_BIT> DataValueType;

#define DATA_SIZE_BYTE (DATA_SIZE_BIT >> 3)
#define KEYNUM (1 <<KEY_HYP_BIT)

typedef unsigned long long KeyDataType;
typedef unsigned long long KeyIndexType;
typedef std::bitset<DATA_SIZE_BIT> IntermediateValueType;
typedef float StatisticValueType;

typedef Eigen::Matrix<TraceValueType,Eigen::Dynamic,BATCH_SIZE> TracesMatrix;
typedef std::vector< DataValueType > DataMatrix;
typedef boost::multi_array< IntermediateValueType,2> IntermediateValueMatrix;
typedef Eigen::Matrix<TraceValueType,Eigen::Dynamic,KEYNUM> PowerModelMatrix;
typedef Eigen::Matrix<StatisticValueType,Eigen::Dynamic,KEYNUM> StatisticIndexMatrix;
#include "includes.h"

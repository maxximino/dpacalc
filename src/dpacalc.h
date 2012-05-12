#pragma once
#include <Eigen/Dense>
#include <bitset>
#include <memory>
#include <tclap/CmdLine.h>
#include "config.h"
#include "utils.hpp"

typedef std::bitset<DATA_SIZE_BIT> DataValueType;

#define DATA_SIZE_BYTE (DATA_SIZE_BIT >> 3)
#define KEY_SIZE_BYTE (KEY_SIZE_BIT >> 3)
#define KEYNUM (1 <<KEY_HYP_BIT)

typedef std::bitset<KEY_SIZE_BIT> KeyDataType;
typedef unsigned long KeyIndexType;
typedef unsigned long long IntermediateValueType;
typedef float StatisticValueType;

typedef Eigen::Matrix<TraceValueType,Eigen::Dynamic,BATCH_SIZE> TracesMatrix;
typedef std::vector< DataValueType > DataMatrix;
typedef Eigen::Matrix<IntermediateValueType,Eigen::Dynamic,KEYNUM> IntermediateValueMatrix;
typedef Eigen::Matrix<TraceValueType,Eigen::Dynamic,KEYNUM> PowerModelMatrix;
typedef Eigen::Matrix<StatisticValueType,Eigen::Dynamic,KEYNUM> StatisticIndexMatrix;

#include <memory>
#include <iostream>
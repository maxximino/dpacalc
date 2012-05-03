#pragma once
#include <Eigen/Dense>
#include <bitset>
#include <memory>

#include "config.h"


typedef unsigned long long DataValueType;

#define DATA_SIZE_BYTE (DATA_SIZE_BIT >> 3)
#define KEYNUM (1 <<KEY_HYP_BIT)

typedef unsigned long long KeyDataType;
typedef unsigned long long KeyIndexType;
typedef unsigned long long IntermediateValueType;

typedef Eigen::Matrix<TraceValueType,BATCH_SIZE,Eigen::Dynamic> TracesMatrix;
typedef std::vector< std::bitset<DATA_SIZE_BIT> > DataMatrix;
typedef Eigen::Matrix<IntermediateValueType,Eigen::Dynamic,KEYNUM> IntermediateValueMatrix;
typedef Eigen::Matrix<TraceValueType,Eigen::Dynamic,KEYNUM> PowerModelMatrix;

#include "includes.h"
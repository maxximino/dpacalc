project(dpacalc)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake)
INCLUDE (${CMAKE_SOURCE_DIR}/../dpacalc-config.cmake)

find_package(Eigen REQUIRED)
find_package(TCLAP REQUIRED)
set( CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror ${CONFIG_DEBUG_OPTIONS} ${CONFIG_OPTIMIZATION_OPTIONS}") 
set(inputsources input/${CONFIG_CLASS_INPUT}.cpp)
set(keygensources keygen/${CONFIG_CLASS_KEYGEN}.cpp)
set(intermediatesources gen_intermediate/${CONFIG_CLASS_INTERMEDIATE}.cpp)
set(powermodelsources gen_powermodel/${CONFIG_CLASS_POWERMODEL}.cpp)
set(statisticsources statisticaltest/${CONFIG_CLASS_STATISTIC}.cpp)
set(execsources exec/${CONFIG_CLASS_EXEC}.cpp)
set(outputsources output/${CONFIG_CLASS_OUTPUT}.cpp)

include( input/${CONFIG_CLASS_INPUT}.cmake OPTIONAL )
include( keygen/${CONFIG_CLASS_KEYGEN}.cmake OPTIONAL )
include( gen_intermediate/${CONFIG_CLASS_INTERMEDIATE}.cmake OPTIONAL )
include( gen_powermodel/${CONFIG_CLASS_POWERMODEL}.cmake OPTIONAL )
include( statisticaltest/${CONFIG_CLASS_STATISTIC}.cmake OPTIONAL )
include( exec/${CONFIG_CLASS_EXEC}.cmake OPTIONAL )
include( output/${CONFIG_CLASS_OUTPUT}.cmake OPTIONAL )



include_directories(${EIGEN_INCLUDE_DIRS} ${TCLAP_INCLUDE_DIR} ${CMAKE_SOURCE_DIR} ${DPACALC_EXTRA_INCLUDES})
configure_file( config.h.in ${CMAKE_SOURCE_DIR}/config.h)
configure_file( includes.h.in ${CMAKE_SOURCE_DIR}/includes.h)
set(DPACALC_SRCS utils.cpp main.cpp ${inputsources} ${keygensources} ${intermediatesources} ${powermodelsources} ${statisticsources} ${execsources}  ${outputsources} )
add_executable(dpacalc ${DPACALC_SRCS})
target_link_libraries(dpacalc ${DPACALC_EXTRA_LIBS})

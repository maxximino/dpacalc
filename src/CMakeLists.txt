project(dpacalc)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake)
INCLUDE (${CMAKE_SOURCE_DIR}/../dpacalc-config.cmake)

find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
set( CMAKE_CXX_FLAGS "-O2 -std=c++0x -Wall -Werror -g") 
FILE(GLOB inputsources input/*.cpp)
FILE(GLOB keygensources keygen/*.cpp)
FILE(GLOB intermediatesources gen_intermediate/*.cpp)
FILE(GLOB powermodelsources gen_powermodel/*.cpp)
FILE(GLOB statisticsources statisticaltests/*.cpp)

configure_file( config.h.in ${CMAKE_SOURCE_DIR}/config.h)
configure_file( includes.h.in ${CMAKE_SOURCE_DIR}/includes.h)
set(DPACALC_SRCS main.cpp ${inputsources} ${keygensources} ${intermediatesources} ${powermodelsources} )# ${statisticsources} )
add_executable(dpacalc ${DPACALC_SRCS})
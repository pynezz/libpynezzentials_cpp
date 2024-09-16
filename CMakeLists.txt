cmake_minimum_required(VERSION 3.29)
project(libpynezzentials_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR})

add_library(libpynezzentials_cpp STATIC pynezzentials/pynezzentials.cpp.old
        pynezzentials/pynezzentials.h)

cmake_minimum_required(VERSION 3.15)

project(crwd)

#include (CTest)  #not doing unit tests buyt this is essentially how

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#enable_testing()

add_subdirectory(src)

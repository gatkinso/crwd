cmake_minimum_required(VERSION 3.15)

project(crwd)

#include (CTest)  #not doing unit tests but this is essentially how
#enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

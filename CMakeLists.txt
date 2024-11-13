cmake_minimum_required(VERSION 3.29)
project(Stock_Information)

set(CMAKE_CXX_STANDARD 14)
#compile flags to match Gradescope test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror") # remove -Wall if you don't want as many warnings treated as errors
# gradescope does use -Werror, so if you remove it here you may run into issues when trying to submit
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(Stock_Information
        src/main.cpp
        src/MaxHeap.h
        src/MaxHeap.cpp)

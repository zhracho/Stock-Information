cmake_minimum_required(VERSION 3.29)
project(Stock_Information)

set(CMAKE_CXX_STANDARD 14)
#compile flags to match Gradescope test environment


add_executable(Stock_Information
        src/main.cpp
        src/MaxHeap.h
        src/MaxHeap.cpp
        src/Stock.cpp
        src/Stock.h
        src/HashTable.cpp
        src/HashTable.h)

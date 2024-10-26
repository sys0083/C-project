cmake_minimum_required(VERSION 3.26)
project(BigInt)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigInt main.cpp
        BigInt.h
        BigInt.cpp)

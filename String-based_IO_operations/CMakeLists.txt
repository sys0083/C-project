cmake_minimum_required(VERSION 3.26)
project(String_based_IO_operations)

set(CMAKE_CXX_STANDARD 17)

add_executable(String_based_IO_operations main.cpp
        Word.h
        Word.cpp
        Word_set.h
        Word_set.cpp
        WordMap.h
        WordMap.cpp
        myCode.h
        myCode.cpp
)

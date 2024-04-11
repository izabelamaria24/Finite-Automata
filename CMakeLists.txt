cmake_minimum_required(VERSION 3.26)
project(Tema_LFA)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tema_LFA
        Lambda-NFA.cpp
        State.cpp
        headers/Lambda-NFA.h
        headers/State.h
        headers/State.h
        main.cpp
        headers/Parser.h
        Parser.cpp)

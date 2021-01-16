cmake_minimum_required(VERSION 3.17)
project(nespp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(deps/rogueutil)

add_executable(nespp
        src/nes/nes.cpp
        main.cpp)
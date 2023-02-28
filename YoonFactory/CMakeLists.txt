cmake_minimum_required(VERSION 3.10)
project(yoonfactory)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES src/*.h src/*.cpp)

add_library(yoonfactory ${SOURCES})
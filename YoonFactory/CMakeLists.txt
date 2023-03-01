cmake_minimum_required(VERSION 3.10)
project(yoonfactory)

set(CMAKE_CXX_STANDARD 20)

# Link the directory for header and library
include_directories(include)

# CMake instructions to make the static library
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(yoonfactory ${SOURCES})
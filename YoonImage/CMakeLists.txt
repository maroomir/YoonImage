cmake_minimum_required(VERSION 3.10)
project(yoonimage)

set(CMAKE_CXX_STANDARD 20)

# Link the directory for header and library
include_directories(include)
# https://github.com/ArashPartow/bitmap#readme
include_directories(bitmap)

# CMake instructions to make the static library
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(yoonimage ${SOURCES})
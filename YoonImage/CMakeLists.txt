cmake_minimum_required(VERSION 3.20)
project(YoonImage)

set(CMAKE_CXX_STANDARD 17)

# Link the directory for header and library
include_directories(./include/bitmap)  # https://github.com/ArashPartow/bitmap#readme

# CMake instructions to make the static library
add_library(YoonImage
        src/Image.cpp src/bitmap.cpp
        src/Image.h src/bitmap.h
        src/enum.h)
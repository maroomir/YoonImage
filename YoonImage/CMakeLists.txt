cmake_minimum_required(VERSION 3.20)
project(YoonImage)

set(CMAKE_CXX_STANDARD 17)

# CMake instructions to make the static library
add_library(YoonImage
        src/image.cpp src/bitmap_factory.cpp
        src/image.h src/bitmap_factory.h
        src/enums.h)
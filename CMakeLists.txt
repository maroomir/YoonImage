cmake_minimum_required(VERSION 3.19)
project(YoonImage)
project(ConsoleTest)

set(CMAKE_CXX_STANDARD 17)

# Link the directory for header and library
include_directories(include/bitmap)  # https://github.com/ArashPartow/bitmap#readme

# CMake instructions to make the static library
add_library(YoonImage
        src/Image.cpp src/Image.h
        src/enum.h)

# CMake instructions to test using the static library
add_executable(ConsoleTest main.cpp)
target_link_libraries(ConsoleTest YoonImage)
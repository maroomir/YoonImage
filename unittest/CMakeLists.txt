cmake_minimum_required(VERSION 3.10)
project(yoonimage-unittest)

include_directories(${YoonFactory_SOURCE_DIR}/YoonImage/include)

link_directories(${YoonFactory_BINARY_DIR}/YoonImage)

add_executable(unit-test main.cpp)

target_link_libraries(unit-test yoonimage)
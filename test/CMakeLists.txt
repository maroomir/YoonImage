cmake_minimum_required(VERSION 3.10)
project(yoonimage-test)

include_directories(${PROJECT_INCLUDE_DIR})

link_directories(${YoonFactory_BINARY_DIR}/YoonImage)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} yoonimage)
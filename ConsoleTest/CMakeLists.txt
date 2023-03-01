include_directories(${YoonFactory_SOURCE_DIR}/YoonImage/include)

link_directories(${YoonFactory_BINARY_DIR}/YoonImage)

add_executable(console-test main.cpp)

target_link_libraries(console-test yoonimage)
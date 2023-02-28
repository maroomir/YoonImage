include_directories(${YoonFactory_SOURCE_DIR}/YoonImage/src)

link_directories(${YoonFactory_BINARY_DIR}/YoonImage)

add_executable(ConsoleTest main.cpp)

target_link_libraries(ConsoleTest yoonimage)
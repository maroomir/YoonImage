# Link the directory for header and library
# https://github.com/ArashPartow/bitmap#readme
include_directories(include/bitmap)

# CMake instructions to make the static library
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(yoonimage ${SOURCES})
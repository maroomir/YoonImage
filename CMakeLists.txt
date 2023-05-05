cmake_minimum_required(VERSION 3.10)
project(yoonimage)

set(CMAKE_CXX_STANDARD 17)

set(PACKAGE_NAME "yoonimage")

# Package 찾기
include(FindPkgConfig)
pkg_check_modules(PKGS REQUIRED ${BUILD_DEPENNDS} libturbojpeg)
message("-- includes=${PKGS_INCLUDE_DIRS}")
message("-- ldflags=${PKGS_LDFLAGS}")

# include directory 설정
# pkg-config 에서 가져온 include 포함
include_directories(include)
include_directories(${PKGS_INCLUDE_DIRS})

# yoonimage 라이브러리 생성
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PACKAGE_NAME} ${SOURCES})

# compile 시 link 설정
# pkg-config 에서 가져온 lib(ldflags) 포함
target_link_libraries(${PACKAGE_NAME} ${PKGS_LDFLAGS})

# unittest debugging
add_subdirectory(unittest)
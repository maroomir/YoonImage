cmake_minimum_required(VERSION 3.10)
project(yoonimage)

set(CMAKE_CXX_STANDARD 17)

# Package 찾기
include(FindPkgConfig)
pkg_check_modules(PROJECT_PKGS REQUIRED
        ${BUILD_DEPENNDS}
        libturbojpeg)
message("-- includes=${PROJECT_PKGS_INCLUDE_DIRS}")
message("-- ldflags=${PROJECT_PKGS_LDFLAGS}")

# include directory 설정
# pkg-config 에서 가져온 include 포함
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_PKGS_INCLUDE_DIRS})

# yoonimage 라이브러리 생성
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${PROJECT_SOURCES})

# compile 시 link 설정
# pkg-config 에서 가져온 lib(ldflags) 포함
target_link_libraries(${PROJECT_NAME} ${PROJECT_PKGS_LDFLAGS})

# test debugging
add_subdirectory(test)
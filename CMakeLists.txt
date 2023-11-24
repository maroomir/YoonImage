cmake_minimum_required(VERSION 3.10)
project(yoonimage)

set(CMAKE_CXX_STANDARD 17)

# Package 찾기
include(FindPkgConfig)
pkg_check_modules(PROJECT_PKGS REQUIRED
        ${BUILD_DEPENNDS}
        libjpeg)
message("-- includes=${PROJECT_PKGS_INCLUDE_DIRS}")
message("-- ldflags=${PROJECT_PKGS_LDFLAGS}")

# include directory 설정
include_directories(${CMAKE_SOURCE_DIR}/include)

# yoonimage 라이브러리 생성
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${PROJECT_SOURCES})

# target include 설정
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_PKGS_INCLUDE_DIRS})

# target link 설정
target_link_libraries(${PROJECT_NAME} ${PROJECT_PKGS_LDFLAGS})

# test debugging
add_subdirectory(test)
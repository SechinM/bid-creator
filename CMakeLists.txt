cmake_minimum_required(VERSION 3.11)
project(bid-creator)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(bid-creator main.cpp)
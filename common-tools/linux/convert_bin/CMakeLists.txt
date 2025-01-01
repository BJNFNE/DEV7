cmake_minimum_required(VERSION 3.29.5)
#cmake_minimum_required(VERSION 3.24)
project(convert_bin)
message("-- convert_bin - CMake compilation")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "-O2")

add_executable(convert_bin convert_bin.cpp)

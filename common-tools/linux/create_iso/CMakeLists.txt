cmake_minimum_required(VERSION 3.28.3)
project(create_iso)
message("-- create_iso - CMake compilation")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "-O2")

add_executable(create_iso create_iso.cpp)

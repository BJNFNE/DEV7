cmake_minimum_required(VERSION 3.28.3)
project(LoaderMDO)
message("-- LoaderMDO - CMake compilation")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "-O2 -pipe -s")

add_executable(LoaderMDO LoaderMDO.cpp)

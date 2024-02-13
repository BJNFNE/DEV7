cmake_minimum_required(VERSION 3.24)
#cmake_minimum_required(VERSION 3.26) (remove # if minimium cmake version should be 3.26)
project(DLLInjector)

set(CMAKE_CXX_STANDARD 17)

add_executable(DLLInjector DLLInjector.cpp)

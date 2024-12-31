cmake_minimum_required(VERSION 3.29.5)
#cmake_minimum_required(VERSION 3.24)
project(DEV7Launcher)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "-O2 -pipe -s")

add_executable(DEV7Launcher DEV7Launcher.cpp)

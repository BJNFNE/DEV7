cmake_minimum_required(VERSION 3.28.3)
project(PLAViewer)
message("-- PLAViewer - CMake compilation")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "-Os")

add_executable(PLAViewer PLAViewer.cpp)

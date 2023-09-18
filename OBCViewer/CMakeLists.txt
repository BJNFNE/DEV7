cmake_minimum_required(VERSION 3.24)
#cmake_minimum_required(VERSION 3.26) (remove # if minimium cmake version should be 3.26)
project(OBCViewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(OBCViewer OBCViewer.cpp)

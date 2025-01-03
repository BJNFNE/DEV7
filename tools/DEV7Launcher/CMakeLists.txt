cmake_minimum_required(VERSION 3.29.5)
#cmake_minimum_required(VERSION 3.24)
project(DEV7Launcher)
message("-- DEV7Launcher - CMake compilation")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "-Od")

# Check if the system is Linux
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Check if unistd.h is available
    include(CheckIncludeFile)
    check_include_file("unistd.h" HAVE_UNISTD_H)

    if(HAVE_UNISTD_H)
        message("--> unistd.h is present on Linux")
    else()
        message("--> unistd.h is NOT present on Linux")
    endif()
else()
    message("--> This is not a Linux system, skipping unistd.h check.")
endif()

add_executable(DEV7Launcher DEV7Launcher.cpp)

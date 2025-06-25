cmake_minimum_required(VERSION 3.29.5)

# Set the project name
project(DEV7)

# Specify where the executables will be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)

include_directories(${CMAKE_SOURCE_DIR})

# Add each tool's directory as a subdirectory
add_subdirectory(tools/BCD1Creator)
add_subdirectory(tools/CTRKViewer)
add_subdirectory(tools/DEV7Launcher)
add_subdirectory(tools/OBCViewer)
add_subdirectory(tools/PLAViewer)
add_subdirectory(tools/OBJDumper)
add_subdirectory(tools/ModelPathDumper)

# Check if we are building on Linux
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Set a separate output directory for Linux binaries
    set(LINUX_BIN_DIR ${CMAKE_SOURCE_DIR}/binaries/linux)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LINUX_BIN_DIR})

    # Only add the Linux-specific program if on Linux
    add_subdirectory(rewritten-software-ports/linux/LoaderMDO)
    add_subdirectory(common-tools/linux/convert_bin)
    add_subdirectory(common-tools/linux/create_iso)
    #add_subdirectory(common-tools/linux/extract_iso)
    add_subdirectory(common-tools/linux/create_tar)
    add_subdirectory(common-tools/linux/create_zip)
else()
    # Set a different output directory for non-Linux binaries
    set(OTHER_BIN_DIR ${CMAKE_SOURCE_DIR}/binaries/linux)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OTHER_BIN_DIR})
endif()

# Optional: Add a custom target to build all tools at once
add_custom_target(all_tools
    DEPENDS BCD1Creator CTRKViewer DEV7Launcher OBCViewer OBJDumper ModelPathDumper LoaderMDO)

cmake_minimum_required(VERSION 3.29.5)

# Set the project name
project(DEV7)

# Specify where the executables will be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)

# Add each tool's directory as a subdirectory
add_subdirectory(tools/BCD1Creator)
add_subdirectory(tools/CTRKViewer)
add_subdirectory(tools/DEV7Launcher)
add_subdirectory(tools/OBCViewer)
add_subdirectory(tools/OBJDumper)
add_subdirectory(tools/ModelPathDumper)

# Optional: Add a custom target to build all tools at once
add_custom_target(all_tools
    DEPENDS BCD1Creator CTRKViewer DEV7Launcher OBCViewer OBJDumper ModelPathDumper)

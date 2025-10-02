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
    #add_subdirectory(common-tools/nowin/convert_bin)
    add_subdirectory(common-tools/linux/create_iso)
    #add_subdirectory(common-tools/linux/extract_iso)
    #add_subdirectory(common-tools/nowin/create_tar)
    #add_subdirectory(common-tools/nowin/create_zip)
else()
    # Set a different output directory for non-Linux binaries
    set(OTHER_BIN_DIR ${CMAKE_SOURCE_DIR}/binaries/linux)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OTHER_BIN_DIR})
endif()

# Optional: Add a custom target to build all tools at once
add_custom_target(all_tools
    DEPENDS BCD1Creator CTRKViewer DEV7Launcher OBCViewer OBJDumper ModelPathDumper LoaderMDO)

# Install commands (Linux only)
option(ENABLE_INSTALL "Enable installation of the project" ON)

if(ENABLE_INSTALL AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(TARGETS BCD1Creator CTRKViewer DEV7Launcher OBCViewer OBJDumper ModelPathDumper LoaderMDO
        RUNTIME DESTINATION bin)

    # Create symlinks for all tools
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/BCD1Creator
        ${CMAKE_INSTALL_PREFIX}/bin/bcd1creator)")

    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/CTRKViewer
        ${CMAKE_INSTALL_PREFIX}/bin/ctrkviewer)")

    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/DEV7Launcher
        ${CMAKE_INSTALL_PREFIX}/bin/dev7launcher)")

    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/OBCViewer
        ${CMAKE_INSTALL_PREFIX}/bin/obcviewer)")

    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/OBJDumper
        ${CMAKE_INSTALL_PREFIX}/bin/objdumper)")

    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/ModelPathDumper
        ${CMAKE_INSTALL_PREFIX}/bin/modelpathdumper)")

    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_INSTALL_PREFIX}/bin/LoaderMDO
        ${CMAKE_INSTALL_PREFIX}/bin/loadermdo)")
endif()

# Uninstall command (Linux only)
if(NOT TARGET uninstall AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/BCD1Creator"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/bcd1creator"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/CTRKViewer"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/ctrkviewer"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/DEV7Launcher"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/dev7launcher"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/OBCViewer"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/obcviewer"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/OBJDumper"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/objdumper"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/ModelPathDumper"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/modelpathdumper"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/LoaderMDO"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/bin/loadermdo"
        COMMENT "Uninstalling the project")
endif()
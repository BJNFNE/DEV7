# Compiling DEV7 Tools

# Supported Compilers
- Windows
* Visual Studio 6.0 (only for LoaderMDO/SYSTEM)
* Visual Studio 2022
* MinGW/gcc
* CMake

- Linux
* gcc
* clang
* meson (WIP)
* CMake

- macOS (Currently unsupported)
* gcc

# Windows
- Visual Studio:
* To to compile LoaderMDO/SYSTEM on Windows take an look at the Code comments.

1. Open the Project directory of the Tool which you want to compile in Visual Studio.
2. Wait until Visual Studio is done with initializing the Project in Visual Studio
3. Now press under Build -> Build (Name of the Tool.exe)
4. You can switch also optionally to Debug builds or Release builds.

- CMake:
* Requirement: CMake 3.29.5
1. Open the root directory of DEV7 in Visual Studio.
2. Wait for generating the project files for the Build system.
3. Now press Build -> Build all
4. The compiled executables are stored in the 'binaries' folder.

- WSL:

1. First install WSL and an dist of your preferences.
2. Set the WSL instance up and update it.
3. Install all required deps, and then run ./configure
4. And now you can run the 'make' command to compile the Tools.
4. For building Debug builds, Run 'make debug'

# Linux
- gcc:
1. Go into the Root directory of DEV7. (If you not already are)
2. Type ./configure and press Enter. The Scripts shows you if you able to compile DEV7 Tools or if any dependencies to compile is missing.
3. Type make and press Enter. This method compiles the DEV7 Tools over gcc.
4. For building Debug builds, Run 'make debug'

- clang:
1. Go into the Root directory of DEV7. (If you not already are)
2. Type ./configure and press Enter. The Scripts shows you if you able to compile DEV7 Tools or if any dependencies to compile is missing.
3. make clang and press Enter. This time DEV7 tools were compiled over clang instead of gcc.

- CMake:
* Requirement: CMake 3.29.5
1. Go into the Root directory of DEV7. (If you not already are)
2. Run ./configure to verify that everything is installed properly to proceed.
3. Run make cmake, after that the binaries while be compiled over CMake.
4. Compiled Binaries can be found in the 'binaries' folder.

# macOS
- gcc:
1. Go into the Root directory of DEV7. (If you you not already are) 
2. First install brew. (If you not already have)
3. Type brew bundle --file=Brewfile, to install the required dependencies. (Optional: Only do it when the dependencies not already installed)
4. Type make and press Enter. 

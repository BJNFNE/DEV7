# Compiling DEV7 Tools

# Supported Compilers
- Windows
* Visual Studio 6.0 (only for LoaderMDO/SYSTEM)
* Visual Studio 2022
* MinGW/gcc

- Linux
* gcc
* clang
* meson (WIP)

- macOS
* gcc

# Windows
- Visual Studio:
* To to compile LoaderMDO/SYSTEM on Windows take an look at the Code comments.

1. Open the Project directory of the Tool which you want to compile in Visual Studio.
2. Wait until Visual Studio is done with initializing the Project in Visual Studio
3. Now press under Build -> Build (Name of the Tool.exe)


# Linux
- gcc:
1. Go into the Root directory of DEV7. (If you not already are)
2. Type ./configure and press Enter. The Scripts shows you if you able to compile DEV7 Tools or if any dependencies to compile is missing.
3. Type make and press Enter. This method compiles the DEV7 Tools over gcc.

- clang:
1. Go into the Root directory of DEV7. (If you not already are)
2. Type ./configure and press Enter. The Scripts shows you if you able to compile DEV7 Tools or if any dependencies to compile is missing.
3. make clang and press Enter. This time DEV7 tools were compiled over clang instead of gcc.

# macOS
- gcc:
1. Go into the Root directory of DEV7. (If you you not already are) 
2. First install brew. (If you not already have)
3. Type brew bundle --file=Brewfile, to install the required dependencies. (Optional: Only do it when the dependencies not already installed)
4. Type make and press Enter. 

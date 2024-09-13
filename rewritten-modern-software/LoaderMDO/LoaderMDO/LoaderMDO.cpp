/*
LoaderMDO was used as Adibou3.EXE in Adibou 3 and as ADI5.EXE in ADI 5.
It was developed to be linked to Loader7.exe to run it.
***********************************************************************
This is a port to the x64 Platform and newer C++. Code based on LoaderMDO's rewritten code, which can be found in /rewritten-original-software/LoaderMDO/LoaderMDO.cpp
It was originally developed for ADI 5 version 5.00 in the Year 2000.
Requirements:
-  Compile under MSVC 2022 or MinGW
-  Compatible with Windows 7 to Windows 11
Compiling:
- Can directly be compiled in MSVC; you can change between Release or Debug mode.
- To compile over g++/MinGW, you can run this command to compile: g++ -o LoaderMDO.exe LoaderMDO.cpp -luser32
- When you want to remove the debug symbols from the exe use the "strip LoaderMDO.exe" (Without quotes) command (g++/MinGW only)
*/

#include <windows.h>
#include <process.h>  // Include for _spawnl

#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    HANDLE MutexA;

    // Create a mutex named "ADI5_LAUNCH_MUTEX"
    MutexA = CreateMutexA(NULL, TRUE, "ADI5_LAUNCH_MUTEX");

    // Check if mutex creation failed or if it already exists
    if (!MutexA || GetLastError() == ERROR_ALREADY_EXISTS) {
        return 0;  // Exit if mutex already exists or creation failed
    }

    // Check if a window with the title "LoaderMDO" exists, and wait if it does
    while (FindWindowA(NULL, "LoaderMDO")) {
        Sleep(100);  // Sleep for 100 milliseconds
    }

    // Launch Loader7.exe using _spawnl
    _spawnl(_P_NOWAIT, "Loader7.exe", "Loader7.exe", "Loader7.exe", NULL);

    // Close the mutex handle after the process is created
    CloseHandle(MutexA);
    return 0;
}

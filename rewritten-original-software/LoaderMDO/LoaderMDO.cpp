/*
LoaderMDO was used as Adibou3.EXE in Adibou 3 and as ADI5.EXE in ADI 5.
It was developed to be linked to Loader7.exe to run it.
***********************************************************************
This is an attempt to recreate that EXE in C++ as it was developed back then by Coktel/MDO.
It was originally developed for ADI 5 version 5.00 in the Year 2000.
Requirements:
-  Compile under MSVC 6.0 build 8168 (Any newer build of MSVC6.0 work aswell but Coktel/MDO used back then used exactly this version of the Compiler.)
Compiling:
- Compile in Release mode to keep it original in Release mode as it was back then. (directly from Visual Studio 6.0)
- build_release.bat: if you compile it over this batch file it whil be smaller then original in size.
- build_debug.bat: if you compile over that batch file you have the exact same filesize with debug symbols included.
*/

#include <windows.h>
#include <process.h>  // Include for _spawnl

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
    _spawnl(_P_NOWAIT, "Loader7.exe", "Loader7.exe", 0, NULL);

    // Close the mutex handle after the process is created
    CloseHandle(MutexA);
	return 0;
}

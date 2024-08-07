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

// Function prototype for starting Loader7.exe with arguments
void startLoader7(int argc, unsigned int* argv);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Check if a window with the title "LoaderMDO" exists
    HWND hwnd = FindWindowA(NULL, "LoaderMDO");
    
    // If a window with the title "LoaderMDO" exists, sleep for 100ms
    while (hwnd != NULL) {
        Sleep(100); // Sleep for 100 milliseconds
        hwnd = FindWindowA(NULL, "LoaderMDO"); // Check again
    }

    // Create the ADI5_LAUNCH_MUTEX
    HANDLE mutex = CreateMutexA(NULL, TRUE, "ADI5_LAUNCH_MUTEX");

    if (mutex != NULL) {
        if (GetLastError() != ERROR_ALREADY_EXISTS) {
            // Mutex does not already exist, so proceed with launching Loader7.exe
            unsigned int args[] = {1, (unsigned int)"Loader7.exe"};
            startLoader7(sizeof(args)/sizeof(args[0]), args);
        }
        CloseHandle(mutex);
        return;
    }

    return;
}

// Function definition for starting Loader7.exe with arguments
void startLoader7(int argc, unsigned int* argv) {
    // Start Loader7.exe
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(NULL, "Loader7.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return;
    }
}

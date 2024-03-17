/*
LoaderMDO was used as Adibou3.EXE in Adibou 3 and as ADI5.EXE in ADI 5.
It was developed to be linked to Loader7.exe to run it.
***********************************************************************
This is just an attempt to recreate that EXE in C++ as it was developed.
It was originally developed for ADI 5 version 5.00 in the Year 2000.
Requirements:
-  Compile under MSVC 6.0
Compiling:
- Compile in Release mode to keep it original in Release mode as it was back then. (directly from Visual Studio 6.0)
- build_release.bat: if you compile it over this batch file it whil be smaller then original in size.
- build_debug.bat: if you compile over that batch file you have the exact same filesize with debug symbols included.
*/

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Check if a window with the title "LoaderMDO" exists
    HWND hwnd = FindWindowA(NULL, "LoaderMDO");
    
    // If no window with the title "LoaderMDO" exists, create the ADI5_LAUNCH_MUTEX
    if (hwnd == NULL) {
        HANDLE mutex = CreateEventA(NULL, TRUE, FALSE, "ADI5_LAUNCH_MUTEX");

        if (mutex != NULL) {
            STARTUPINFOA si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            // Command line to start Loader7.exe
            LPSTR commandLine = "Loader7.exe";

            // Start Loader7.exe
            if (CreateProcessA(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }

            CloseHandle(mutex);
        }
    }

    return 0;
}


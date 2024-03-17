/*
LoaderMDO was used as Adibou3.EXE in Adibou 3 and as ADI5.EXE in ADI 5.
It was developed to be linked to Loader7.exe to run it.
***********************************************************************
This is an port to the x64 Platform and newer C++. Code based on LoaderMDO's rewritten code. which can be found in /rewritten-original-software/LoaderMDO/LoaderMDO.cpp
It was originally developed for ADI 5 version 5.00 in the Year 2000.
Requirements:
-  Compile under MSVC 2022
Compiling:
- Can directly be compiled in MSVC you can change between Release or Debug mode.
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <thread> // for std::this_thread::sleep_for

#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Check if a window with the title "LoaderMDO" exists
    HWND hwnd = FindWindowW(NULL, L"LoaderMDO");

    // If a window with the title "LoaderMDO" exists, sleep for 100ms
    while (hwnd != NULL) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        hwnd = FindWindowW(NULL, L"LoaderMDO"); // Check again
    }

    // Create the ADI5_LAUNCH_MUTEX
    HANDLE mutex = CreateMutexW(NULL, TRUE, L"ADI5_LAUNCH_MUTEX");

    if (mutex != NULL) {
        if (GetLastError() != ERROR_ALREADY_EXISTS) {
            // Mutex does not already exist, so proceed with launching Loader7.exe

            STARTUPINFOW si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            // Command line to start Loader7.exe
            std::wstring commandLine = L"Loader7.exe";

            // Start Loader7.exe
            if (CreateProcessW(NULL, const_cast<LPWSTR>(commandLine.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
        }
        CloseHandle(mutex);
    }

    return 0;
}


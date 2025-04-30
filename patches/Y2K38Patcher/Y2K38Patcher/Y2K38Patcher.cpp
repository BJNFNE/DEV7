// Ported over from SetupPatcher
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <ctime>
#include <string>

// TODO:
// Change the clock date back to the realtime value when the process (setup.exe) is being closed/terminated.
// Current Workaround, sync the Time between PC and Time Server over the Settings, to change it back to the current timedate

// Function to find the process ID of a given process name
DWORD GetProcessId(const TCHAR* processName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnap, &pe32)) {
        CloseHandle(hSnap);
        return 0;
    }

    do {
        if (_tcsicmp(pe32.szExeFile, processName) == 0) {
            CloseHandle(hSnap);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hSnap, &pe32));

    CloseHandle(hSnap);
    return 0;
}

int main() {
    // Get the current system time
    SYSTEMTIME originalSysTime;
    GetLocalTime(&originalSysTime);

    // Emulate the year 2022
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
    sysTime.wYear = 2022;
    SetSystemTime(&sysTime);

    const TCHAR* loaderExeName = TEXT("Loader7.exe");
    const TCHAR* devExeName = TEXT("Dev7VM.EXE");

    // Get the directory path of the current executable
    TCHAR exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);
    TCHAR* lastBackslash = _tcsrchr(exePath, '\\');
    if (lastBackslash != NULL)
        *lastBackslash = '\0'; // Null-terminate at the last backslash

    // Construct full path to Loader7.exe
    TCHAR loaderExePath[MAX_PATH];
    _stprintf_s(loaderExePath, MAX_PATH, TEXT("%s\\%s"), exePath, loaderExeName);

    // Execute the Loader7.exe process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    BOOL success = CreateProcess(NULL, loaderExePath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    printf("When you done playing your DEV7 game, set the Date back to the one you currently have.\n");

    if (!success) {
        std::cerr << "Failed to execute Loader7.exe." << std::endl;
        std::cout << "Press Enter to exit\n" << std::endl;
        std::cin.get();
        return 1;
    }

    // Wait for the Loader7.exe process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Construct full path to Dev7VM.EXE
    TCHAR devExePath[MAX_PATH];
    _stprintf_s(devExePath, MAX_PATH, TEXT("%s\\%s"), exePath, devExeName);

    // Execute the Dev7VM.EXE process
    success = CreateProcess(NULL, devExePath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    if (!success) {
        std::cerr << "Failed to execute Dev7VM.EXE." << std::endl;
        std::cout << "Press Enter to exit\n" << std::endl;
        std::cin.get();
        return 1;
    }

    // Wait for the Dev7VM.EXE process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Restore the original system time
    SetSystemTime(&originalSysTime);

    // Close process and thread handles
    printf("When you done playing your DEV7 game, set the Date back to the one you currently have.\n");
    printf("Pres Enter to exit Y2K38Patcher\n");
    std::cin.get();
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

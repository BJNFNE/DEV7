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

    const TCHAR* exeName = TEXT("setup.exe");

    // Get the directory path of the current executable
    TCHAR exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);
    TCHAR* lastBackslash = _tcsrchr(exePath, '\\');
    if (lastBackslash != NULL)
        *lastBackslash = '\0'; // Null-terminate at the last backslash

    // Construct full path to setup.exe
    TCHAR setupExePath[MAX_PATH];
    _stprintf_s(setupExePath, MAX_PATH, TEXT("%s\\%s"), exePath, exeName);

    // Execute the setup.exe process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    BOOL success = CreateProcess(NULL, setupExePath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    if (!success) {
        std::cerr << "Failed to execute setup.exe." << std::endl;
        return 1;
    }

    // Wait for the process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Restore the original system time
    SetSystemTime(&originalSysTime);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

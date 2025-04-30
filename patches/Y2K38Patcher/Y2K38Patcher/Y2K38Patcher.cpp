#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <ctime>
#include <string>

bool IsUser AnAdmin() {
    BOOL isAdmin = FALSE;
    PSID administratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &administratorsGroup)) {
        if (!CheckTokenMembership(NULL, administratorsGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        FreeSid(administratorsGroup);
    }
    return isAdmin;
}

void ShowAdminWarning() {
    MessageBox(NULL, TEXT("This application requires administrative rights to change the system time."), TEXT("Warning"), MB_OK | MB_ICONWARNING);
}

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
    // Check if the application is running with administrative rights
    if (!IsUser AnAdmin()) {
        ShowAdminWarning();
        return 1; // Exit if not running as admin
    }

    // Get the current system time
    SYSTEMTIME originalSysTime;
    GetLocalTime(&originalSysTime);

    // Emulate the year 2022
    SYSTEMTIME sysTime;
    sysTime.wYear = 2022;
    sysTime.wMonth = 1; // January
    sysTime.wDay = 1;   // 1st
    sysTime.wHour = 0;  // 00:00:00
    sysTime.wMinute = 0;
    sysTime.wSecond = 0;
    sysTime.wMilliseconds = 0;

    // Set the system time to the specified date
    if (!SetLocalTime(&sysTime)) {
        std::cerr << "Failed to set system time. Error: " << GetLastError() << std::endl;
        return 1;
    }

    const TCHAR* exeName = TEXT("Loader7.exe");

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
        std::cerr << "Failed to execute Loader7.exe. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // Wait for the process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Restore the original system time
    if (!SetLocalTime(&originalSysTime)) {
        std::cerr << "Failed to restore original system time. Error: " << GetLastError() << std::endl;
    }

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Y2K38Patcher patched temp the Game, Enjoy your Game session and be nostalgic :)" << std::endl
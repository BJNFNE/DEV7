#include <iostream>
#include <windows.h>
#include <string>
#include <pdh.h>
#include <Psapi.h>
#include <TlHelp32.h>

#include "common-code/ConsoleUtils.h"

#pragma comment(lib, "pdh.lib")

using namespace std;

const wstring LOADER_EXE_NAME = L"Loader7.exe";
const wstring LOADER_EXE_PARAM = L"-break";

bool isProcessRunning(const wstring& processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe32)) {
        CloseHandle(hSnapshot);
        return false;
    }

    do {
        if (processName == pe32.szExeFile) {
            CloseHandle(hSnapshot);
            return true;
        }
    } while (Process32Next(hSnapshot, &pe32));

    CloseHandle(hSnapshot);
    return false;
}

void startLoader7() {
    wstring command = L"\"" + LOADER_EXE_NAME + L"\" " + LOADER_EXE_PARAM;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "Failed to start Loader7.exe.");
    }
    else {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

DWORD GetProcessId(const wstring& processName) {
    DWORD processId = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe32)) {
            do {
                if (processName == pe32.szExeFile) {
                    processId = pe32.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }
    return processId;
}

double GetCPULoad(DWORD processId) {
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuCounter;

    PdhOpenQuery(NULL, NULL, &cpuQuery);
    PdhAddCounter(cpuQuery, (L"\\Process(" + to_wstring(processId) + L")\\% Processor Time").c_str(), NULL, &cpuCounter);
    PdhCollectQueryData(cpuQuery);
    Sleep(1000);

    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuCounter, PDH_FMT_DOUBLE, NULL, &counterVal);

    PdhCloseQuery(cpuQuery);

    return counterVal.doubleValue;
}

double GetMemoryUsage(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL) {
        return -1;
    }

    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(hProcess, reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc))) {
        CloseHandle(hProcess);
        return -1;
    }

    CloseHandle(hProcess);
    return pmc.PrivateUsage / (1024.0 * 1024.0);
}

int main() {
    if (!isProcessRunning(LOADER_EXE_NAME)) {
        startLoader7();
    }

    while (true) {
        ConsoleUtils::clearConsole();

        double cpuUsage = GetCPULoad(GetProcessId(LOADER_EXE_NAME));

        if (cpuUsage != -1) {
            double loaderMemoryUsage = GetMemoryUsage(GetProcessId(LOADER_EXE_NAME));
            wcout << L"Loader7.exe Memory Usage: " << loaderMemoryUsage << L" MB" << endl;
        }

        wcout << L"CPU Usage: " << cpuUsage << L"%" << endl;

        // Check if Loader7.exe process is still running
        if (!isProcessRunning(LOADER_EXE_NAME)) {
            printf("Loader7.exe process stopped. Exiting DEV7Monitor.");
            break;
        }

        Sleep(5000); // Wait for 5 seconds before checking again
    }

    return 0;

} // End of namespace std

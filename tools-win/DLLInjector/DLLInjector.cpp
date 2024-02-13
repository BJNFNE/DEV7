#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;

const string exeName1 = "loader7.exe";
const string exeName2 = "Dev7VM.EXE";
const string dllPath = "CustomDLL.dll";

bool InjectDLL(DWORD processId, const string& dllPath) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (hProcess == NULL) {
        cout << "Failed to open process. Error code: " << GetLastError() << endl;
        return false;
    }

    LPVOID dllPathAddr = VirtualAllocEx(hProcess, NULL, dllPath.size() + 1, MEM_COMMIT, PAGE_READWRITE);
    if (dllPathAddr == NULL) {
        cout << "Failed to allocate memory in the target process. Error code: " << GetLastError() << endl;
        CloseHandle(hProcess);
        return false;
    }

    if (!WriteProcessMemory(hProcess, dllPathAddr, dllPath.c_str(), dllPath.size() + 1, NULL)) {
        cout << "Failed to write DLL path into the target process. Error code: " << GetLastError() << endl;
        VirtualFreeEx(hProcess, dllPathAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    HMODULE hKernel32 = GetModuleHandle(L"kernel32.dll");
    if (hKernel32 == NULL) {
        cout << "Failed to get handle to kernel32.dll. Error code: " << GetLastError() << endl;
        VirtualFreeEx(hProcess, dllPathAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    LPTHREAD_START_ROUTINE loadLibraryAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryA");
    if (loadLibraryAddr == NULL) {
        cout << "Failed to get address of LoadLibraryA. Error code: " << GetLastError() << endl;
        VirtualFreeEx(hProcess, dllPathAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, loadLibraryAddr, dllPathAddr, 0, NULL);
    if (hThread == NULL) {
        cout << "Failed to create remote thread in the target process. Error code: " << GetLastError() << endl;
        VirtualFreeEx(hProcess, dllPathAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    CloseHandle(hThread);
    CloseHandle(hProcess);
    return true;
}

DWORD GetProcessIdByName(const string& processName) {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        cout << "Failed to create process snapshot. Error code: " << GetLastError() << endl;
        return 0;
    }
    if (!Process32First(hSnapshot, &pe32)) {
        cout << "Failed to retrieve first process. Error code: " << GetLastError() << endl;
        CloseHandle(hSnapshot);
        return 0;
    }
    do {
        if (processName == pe32.szExeFile) {
            CloseHandle(hSnapshot);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hSnapshot, &pe32));
    CloseHandle(hSnapshot);
    return 0;
}

int main() {
    DWORD processId1 = GetProcessIdByName(exeName1);
    DWORD processId2 = GetProcessIdByName(exeName2);

    if (processId1 != 0 && InjectDLL(processId1, dllPath)) {
        cout << "Custom DLL injected successfully into " << exeName1 << "!" << endl;
    } else {
        cout << "Failed to inject Custom DLL into " << exeName1 << "." << endl;
    }

    if (processId2 != 0 && InjectDLL(processId2, dllPath)) {
        cout << "Custom DLL injected successfully into " << exeName2 << "!" << endl;
    } else {
        cout << "Failed to inject Custom DLL into " << exeName2 << "." << endl;
    }

    return 0;
}


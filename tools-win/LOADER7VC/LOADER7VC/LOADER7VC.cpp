#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Shlwapi.h>
#include <iomanip>

#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Shlwapi.lib")

void PrintHeader() {
    std::string versionNumber = "v1.5-testing";
    std::cout << "============================\n";
    std::cout << "LOADER7VC " << versionNumber << "\n";
    std::cout << "============================\n";
}

bool ValidateFilePath(const std::string& filePath) {
    return StrStrIA(filePath.c_str(), "Loader7.exe") || StrStrIA(filePath.c_str(), "Dev7VM.EXE");
}

void PrintVersionInfo(const std::string& filename) {
    DWORD dummy;
    DWORD size = GetFileVersionInfoSizeA(filename.c_str(), &dummy);
    if (size == 0) {
        std::cout << "No version info found.\n";
        return;
    }

    std::vector<char> data(size);
    if (!GetFileVersionInfoA(filename.c_str(), 0, size, data.data())) {
        std::cout << "GetFileVersionInfo failed.\n";
        return;
    }

    VS_FIXEDFILEINFO* verInfo = nullptr;
    UINT len = 0;
    if (VerQueryValueA(data.data(), "\\", reinterpret_cast<LPVOID*>(&verInfo), &len)) {
        std::cout << "Version: "
            << HIWORD(verInfo->dwFileVersionMS) << "."
            << LOWORD(verInfo->dwFileVersionMS) << "."
            << HIWORD(verInfo->dwFileVersionLS) << "."
            << LOWORD(verInfo->dwFileVersionLS) << "\n";
    }

    struct StringInfo {
        LPCSTR name;
        const char* label;
    };

    StringInfo fields[] = {
        {"OriginalFilename", "Original Filename"},
        {"FileDescription",  "Description"},
        {"ProductName",      "Productname"},
        {"InternalName",     "Internalname"},
        {"LegalCopyright",   "Copyright"},
        {"Language",         "Language"},
    };

    LPVOID pBuffer = nullptr;
    UINT cbTranslate = 0;
    if (VerQueryValueA(data.data(), "\\VarFileInfo\\Translation", &pBuffer, &cbTranslate)) {
        WORD* langCode = (WORD*)pBuffer;
        char subBlock[100];
        for (auto& field : fields) {
            sprintf_s(subBlock, "\\StringFileInfo\\%04x%04x\\%s", langCode[0], langCode[1], field.name);
            LPVOID val = nullptr;
            UINT size;
            if (VerQueryValueA(data.data(), subBlock, &val, &size)) {
                std::cout << field.label << ": " << (char*)val << "\n";
            }
            else {
                std::cout << field.label << ": Not available.\n";
            }
        }
    }
}

std::string GetPrintableString(const std::string& input) {
    std::string output;
    for (char c : input) {
        if (isprint(static_cast<unsigned char>(c)) || isspace(static_cast<unsigned char>(c))) {
            output += c;
        }
    }
    return output;
}

void DisplayFileInfo(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return;
    }

    // Read entire file into memory (only for small files)
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    std::cout << "\nInfos about " << filepath << ":\n\n";

    PrintVersionInfo(filepath);

    std::ifstream sizeFile(filepath, std::ios::binary | std::ios::ate);
    std::cout << "File Size: " << sizeFile.tellg() << " Bytes\n";

    size_t nb10Index = content.find("NB10");
    if (nb10Index != std::string::npos) {
        std::string afterNB10 = content.substr(nb10Index + 4);
        std::string pdbPath = GetPrintableString(afterNB10);
        std::cout << "PDB File: " << pdbPath << "\n";
    }
    else {
        std::cout << "PDB File reference not found in " << filepath << "\n";
    }

    std::cout << "\nPress Enter to exit LOADER7VC...";
    std::cin.get();
}

int main(int argc, char* argv[]) {
    PrintHeader();

    std::string exePath;

    if (argc > 1) {
        exePath = argv[1];
        if (!ValidateFilePath(exePath)) {
            std::cerr << "Only Loader7.exe or Dev7VM.EXE are allowed.\n";
            return 1;
        }
    }
    else {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string dirPath = buffer;
        dirPath = dirPath.substr(0, dirPath.find_last_of("\\/"));

        std::string loader7 = dirPath + "\\Loader7.exe";
        std::string dev7vm = dirPath + "\\Dev7VM.EXE";

        if (PathFileExistsA(loader7.c_str())) {
            exePath = loader7;
        }
        else if (PathFileExistsA(dev7vm.c_str())) {
            exePath = dev7vm;
        }
        else {
            std::cerr << "Loader7.exe or Dev7VM.EXE not found in the current directory.\n";
            std::cout << "Press Enter to exit.\n";
            std::cin.get();
            return 1;
        }
    }

    DisplayFileInfo(exePath);
    return 0;
}

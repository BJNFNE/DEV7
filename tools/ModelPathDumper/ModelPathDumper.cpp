/*
ModelPathDumper

EXO files are used by following Games:
- Adi 5
- Adibou 3
- Nathan Vacances series
*/

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void printHeader() {
    const std::string versionNumber = "0.2.0";

    printf("===========================");
    std::cout << " ModelPathDumper ver. " << versionNumber << std::endl;
    printf("===========================");
}

void searchAndDumpPaths(const fs::path& directory, const std::string& outputFile, int& fileCount) {
    std::ofstream output(outputFile);
    if (!output) {
        std::cerr << "Error: Unable to open the output file.\n" << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".exo") {
            std::ifstream file(entry.path());
            if (!file) {
                std::cerr << "Error: Unable to open " << entry.path() << std::endl;
                continue;
            }

            std::string line;
            while (getline(file, line)) {
                if (line.find("Path=C:\\") != std::string::npos || line.find("Path=Y:\\") != std::string::npos) {
                    // Extract only the part of the line after "Path=" and write it to the output file
                    size_t pos = line.find("Path=");
                    if (pos != std::string::npos) {
                        output << entry.path().string() << ": " << line.substr(pos + 5) << std::endl;
                    }
                }
            }
            fileCount++;
        }
    }
}

int main() {
    printHeader();
    std::string directoryPath;
    std::cout << "Enter the directory path: \n";
    std::cout << "If you are already in the correct directory just type .\n";
    std::cin >> directoryPath;

    std::string outputFile;
    std::cout << "Enter the output file path: ";
    std::cin >> outputFile;

    fs::path directory(directoryPath);
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "Error: The specified directory does not exist or is not a directory.\n" << std::endl;
        return 1;
    }

    int exoCount = 0;
    searchAndDumpPaths(directory, outputFile, exoCount);

    std::cout << "Search is completed. Found " << exoCount << " .exo files.\n" << std::endl;
    return 0;
    
} // End of namespace fs

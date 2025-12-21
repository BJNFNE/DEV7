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
    char versionNumber[6] = "0.2.0";

    printf("===========================\n");
    printf("ModelPathDumper ver. %s\n", versionNumber);
    printf("===========================\n");
}

void searchAndDumpPaths(const fs::path& directory, const std::string& outputFile, int& fileCount) {
    std::ofstream output(outputFile);
    if (!output) {
        fprintf(stderr, "Error: Unable to open the output file.");
        return;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".exo") {
            std::ifstream file(entry.path());
            if (!file) {
                fprintf(stderr, "Error: Unable to open %s", entry.path());
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
    printf("Enter the directory path\n");
    printf("If you are already in the correct directory just type.\n");
    std::cin >> directoryPath;

    std::string outputFile;
    printf("Enter the output file path: ");
    std::cin >> outputFile;

    fs::path directory(directoryPath);
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        fprintf(stderr, "Error: The specified directory does not exist or is not a directory.");
        return 1;
    }

    int exoCount = 0;
    searchAndDumpPaths(directory, outputFile, exoCount);
    printf("Search is completed. Found %d .exo files.", exoCount);
    return 0;
    
} // End of namespace fs
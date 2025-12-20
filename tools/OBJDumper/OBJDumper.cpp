#include <iostream>
#include <fstream>
#include <set>
#include <filesystem>

// TODO: fix that OBJDumper creates every secound line an unneeded line that only contains .obj without any linked Folder

namespace fs = std::filesystem;

void printHeader() {
    char versionNumber[6] = "0.5.0";

    printf("=========================\n");
    printf("OBJDumper ver. %s\n", versionNumber);
    printf("=========================\n");
}

// Function to extract unique .obj filenames and dump them to a text file
void extractObjFilenames(const std::string& inputFile, const std::string& outputLocation, bool useSlash) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        fprintf(stderr, "Error: Unable to open input file\n");
        return;
    }

    std::set<std::string> objFiles;
    std::string line;
    while (getline(inFile, line)) {
        if (line.find(".obj") != std::string::npos && line.find_first_not_of(' ') == std::string::npos) {
            // Skip lines containing only ".obj"
            continue;
        }
        size_t found = line.find(".obj");
        if (found != std::string::npos) {
            size_t start = line.rfind(' ', found);
            size_t end = line.find(' ', found);
            if (start == std::string::npos) {
                start = 0;
            } else {
                start++;
            }
            std::string objName = line.substr(start, end - start);
            objFiles.insert(objName);
        }
    }

    // Check if the user prefers using forward slash or colon in the output file format
    std::string delimiter = useSlash ? "/" : ":";

    std::ofstream outFile(outputLocation);
    if (!outFile) {
        if (!useSlash) {
            // Try to create a text file instead of a directory
            outFile.open(outputLocation + ".txt");
            if (!outFile) {
                fprintf(stderr, "Error: Unable to create output file");
                return;
            }
        } else {
            fprintf(stderr,"Error: Unable to open output file");
            return;
        }
    }

    for (const auto& objFile : objFiles) {
        // Replace colon with forward slash if needed and if colon is found
        std::string modifiedObjFile = objFile;
        if (useSlash && modifiedObjFile.find(':') != std::string::npos) {
            size_t pos = modifiedObjFile.find(':');
            modifiedObjFile.replace(pos, 1, "/");
        }
        outFile << modifiedObjFile << ".obj" << std::endl;
    }

    printf(".obj filenames have been dumped sucessfully\n");
}

int main() {
    printHeader();
    std::string inputFile = "loader7.map";
    std::string outputLocation;
    bool useSlash;

    // Get user input for input file
    printf("Enter the input file (default is loader7.map): ");
    getline(std::cin, inputFile);

    // Ask user for output file format preference
    printf("Do you want to use 'Folder/Object.obj' format? (y/n): ");
    std::string preference;
    getline(std::cin, preference);
    useSlash = (preference == "y");

    // Get user input for output location
    printf("Enter the output file name: ");
    getline(std::cin, outputLocation);

    extractObjFilenames(inputFile, outputLocation, useSlash);
    return 0;

} // End of namespace fs
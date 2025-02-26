#include <iostream>
#include <fstream>
#include <set>
#include <filesystem>

// TODO: fix that OBJDumper creates every secound line an unneeded line that only contains .obj without any linked Folder

namespace fs = std::filesystem;

void printHeader() {
    const std::string versionNumber = "0.5.0";

    std::cout << "=========================" << std::endl;
    std::cout << " OBJDumper ver. " << versionNumber << std::endl;
    std::cout << "=========================" << std::endl;
}

// Function to extract unique .obj filenames and dump them to a text file
void dumpUniqueObjFiles(const std::string& inputFile, const std::string& outputLocation, bool useSlash) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Unable to open input file " << inputFile << std::endl;
        return;
    }

    std::set<std::string> objFiles;
    std::string line;
    while (std::getline(inFile, line)) {
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
                std::cerr << "Error: Unable to create output file " << outputLocation << ".txt" << std::endl;
                return;
            }
        } else {
            std::cerr << "Error: Unable to open output file " << outputLocation << std::endl;
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

    std::cout << "Unique .obj filenames have been dumped to " << outputLocation << std::endl;
}

int main() {
    printHeader();
    std::string inputFile = "loader7.map"; // Default input file
    std::string outputLocation;
    bool useSlash;

    // Get user input for input file
    std::cout << "Enter the input file (default is loader7.map): ";
    std::getline(std::cin, inputFile);

    // Ask user for output file format preference
    std::cout << "Do you want to use 'Folder/Object.obj' format? (y/n): ";
    std::string preference;
    std::getline(std::cin, preference);
    useSlash = (preference == "y");

    // Get user input for output location
    std::cout << "Enter the output file name: ";
    std::getline(std::cin, outputLocation);

    dumpUniqueObjFiles(inputFile, outputLocation, useSlash);

    return 0;

} // End of namespace fs 

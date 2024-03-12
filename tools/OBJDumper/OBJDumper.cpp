#include <iostream>
#include <fstream>
#include <string>
#include <set>

// Function to extract unique .obj filenames and dump them to a text file
void dumpUniqueObjFiles(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Unable to open input file " << inputFile << std::endl;
        return;
    }

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Unable to open output file " << outputFile << std::endl;
        return;
    }

    std::set<std::string> objFiles;
    std::string line;
    while (std::getline(inFile, line)) {
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

    for (const auto& objFile : objFiles) {
        outFile << objFile << std::endl;
    }

    std::cout << "Unique .obj filenames have been dumped to " << outputFile << std::endl;
}

int main() {
    std::string inputFile = "loader7.map"; // Default input file
    std::string outputFile;

    // Get user input for input file
    std::cout << "Enter the input file (default is loader7.map): ";
    std::getline(std::cin, inputFile);

    // Get user input for output file
    std::cout << "Enter the output file name: ";
    std::getline(std::cin, outputFile);

    dumpUniqueObjFiles(inputFile, outputFile);

    return 0;
}


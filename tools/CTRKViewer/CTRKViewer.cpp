// CTRKViewer is based on OBCViewer

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

#include "common-code/ConsoleUtils.h"

#ifdef __unix__
#include <unistd.h>
#endif

namespace fs = std::filesystem;

const std::string versionNumber = "1.0";

void printHeader() {
    printf("======================");
    printf("      CTRKViewer      ");
    printf("======================");
}

void printUsage() {
    printHeader();
    printf("Usage: ./CTRKViewer <file.ctrk>");
    std::cout << "Version - " << versionNumber << std::endl << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    // Here are listed the strings for CTRK itself.
    std::string inputCTRK = argv[1];

    // Use the CTRK File for Input
    std::ifstream CTRKInput(inputCTRK);

    if (!CTRKInput) {
        fprintf(stderr, "Error: Unable to find CTRK File.");
        return 1;
    }

    // Rewind the CTRK Script back to the beginning
    CTRKInput.seekg(0);

    // Open the output file for the CTRK Script
    fs::path inputFile(inputCTRK);
    std::ofstream CTRKOutput(inputFile.stem().string() + ".txt");

    if (!CTRKOutput) {
        fprintf(stderr, "Error: Unable to create a text output of the CTRK Script.");
        return 1;
    }

    // Close input & output for CTRK Script
    CTRKInput.close();
    CTRKOutput.close();

    std::cout << "CTRK File (" << argv[1] << ") is now displayable, and the output is saved to " << inputFile.stem().string() << ".txt" << std::endl;

    // Exit message for CTRKViewer
    ConsoleUtils::printNewLine();
    printf("Press Enter to exit CTRKViewer");
    (void)getchar();
    ConsoleUtils::clearConsole(); 
    return 0;

} // End of namespace fs

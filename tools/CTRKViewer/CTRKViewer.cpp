// CTRKViewer is based on OBCViewer

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

#include "common-code/ConsoleUtils.h"
#include "common-code/TaskExecution.h"

#ifdef __unix__
#include <unistd.h>
#endif

namespace fs = std::filesystem;

char versionNumber[6] = "1.0.1";

void printHeader() {
    printf("======================");
    printf("      CTRKViewer      ");
    printf("======================");
}

void printUsage() {
    printHeader();
    printf("Usage: ./CTRKViewer <file.ctrk>");
    printf("%s", versionNumber);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    // Here are listed the strings for CTRK itself.
    std::string ctrkArgv = argv[1];

    // Use the CTRK File for Input
    std::ifstream CTRKInput(ctrkArgv);

    if (!CTRKInput) {
        fprintf(stderr, "Error: Unable to find CTRK File.");
        return 1;
    }

    // Rewind the CTRK Script back to the beginning
    CTRKInput.seekg(0);

    // Open the output file for the CTRK Script
    fs::path inputFile(ctrkArgv);
    std::ofstream CTRKOutput(inputFile.stem().string() + ".txt");

    if (!CTRKOutput) {
        fprintf(stderr, "Error: Unable to create a text output of the CTRK Script.\n");
        return 1;
    }

    // Close input & output for CTRK Script
    CTRKInput.close();
    CTRKOutput.close();

    std::cout << "CTRK File (" << ctrkArgv[1] << ") is now displayable, and the output is saved to " << inputFile.stem().string() << ".txt" << std::endl;

    TaskExecution::pressEnterToExit();
    return 0;

} // End of namespace fs

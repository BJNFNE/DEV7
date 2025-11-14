#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

#include "common-code/ConsoleUtils.h"

#ifdef __unix__
#include <unistd.h>
#elif __APPLE__
#include "../../../../../Library/Developer/CommandLineTools/SDKs/MacOSX15.5.sdk/usr/include/unistd.h"
#endif

namespace fs = std::filesystem;

const std::string versionNumber = "1.7";

void printHeader() {
    std::cout << "======================" << std::endl;
    std::cout << "      OBCViewer       " << std::endl;
    std::cout << "======================" << std::endl;
}

void printUsage() {
    printHeader();
    printf("Usage: ./OBCViewer <script.obc>\n");
    std::cout << "Version - " << versionNumber << std::endl << std::endl;
    printf("Supported games:\n");
    printf(" * Adi 5\n");
    printf(" * Adibou 3\n");
    printf(" * Adibou presente series\n");
    printf(" * Adiboud'chou series\n");
    printf(" * Nathan Vacances series\n");
    printf(" * Le Pays des pierres magiques\n");
    ConsoleUtils::printNewLine();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    std::string inputOBC = argv[1];

    #ifdef __unix__
    // List here everything for the Debug Infos.
    std::string username = getlogin();
    #elif __APPLE__
    std::string username = getlogin();
    #endif

    // Check if the input file is an OBC Script.
    fs::path inputFile(inputOBC);
    if (inputFile.extension() != ".obc") {
        fprintf(stderr, "Error: This File is not an OBC Script!");
        return 1;
    }

    // Use the OBC Script for Input
    std::ifstream OBCInput(inputOBC);

    if (!OBCInput) {
        fprintf(stderr, "Error: Unable to load OBC Script.");
        return 1;
    }
    
    std::string checkEntrypoint;
    char c;
    for (int i = 0; i < 25 && OBCInput.get(c); ++i) {
        checkEntrypoint += c;
    }

    // Uses the OBC Copyright MDO as Entrypoint adds automatically also the last four number of the Year.
    // (usually it is 1999, due to OBCEditor it is possible to change this Year so this Change is made so the modified Scripts are always compatible with OBCViewer)
    int number;
    if (sscanf(checkEntrypoint.c_str(), "OBC Copyright MDO %d", &number) != 1) {
        fprintf(stderr, "Error: Unable to find the Entrypoint!");
        return 1;
    }

    // Rewind the OBC Script back to the beginning
    OBCInput.seekg(0);

    // Open the output file for the OBC Script
    std::ofstream outputScript(inputFile.stem().string() + ".txt");

    if (!outputScript) {
        fprintf(stderr, "Error: Unable to create a text output of the OBC Script");
        return 1;
    }

    // Adds the Date when Output file was created to the Output file
    time_t current_time = time(nullptr);
    char timedate[100];
    strftime(timedate, sizeof(timedate), "%Y-%m-%d %H:%M:%S", localtime(&current_time));

    // Read from input and write to output, keeping track of the offset
    std::streampos offset = OBCInput.tellg();
    while (OBCInput.get(c)) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            outputScript.put(c);
            offset = OBCInput.tellg(); // Update the offset after each character is processed
        }
    }

    // Close input & output for OBC Script
    OBCInput.close();
    outputScript.close();

    // Create a separate file for Debug Infos
    std::ofstream DebugInfoOutput(inputFile.stem().string() + "_debuginfo.txt");
    if (!DebugInfoOutput) {
        fprintf(stderr, "Error: Unable to create Debug Infos file.");
        return 1;
    }

    // Write Debug Infos to the separate file
    DebugInfoOutput << "Debug Infos:" << std::endl;
    DebugInfoOutput << "Output of " << inputFile.stem().string() << ".obc" << " created at " << timedate << std::endl;
    #ifdef __unix__
    DebugInfoOutput << "Created by " << username << std::endl;
    #elif __APPLE__
    DebugInfoOutput << "Created by " << username << std::endl;
    #endif
    DebugInfoOutput << "Offset (hex): 0x" << std::hex << offset << " hex" << std::dec << std::endl;
    DebugInfoOutput << "Offset (bytes): " << offset << " bytes" << std::dec << std::endl;
    DebugInfoOutput.close();

    printf("OBC Script (%s) is now readable\n", argv[1]);

    // Display the full path of the output file of the OBC Script
    ConsoleUtils::printNewLine();
    printf("Output created at:");
    printf("%s", fs::absolute(inputFile.stem().string() + ".txt").c_str());
    ConsoleUtils::printNewLine();

    // Exit message for OBCViewer
    ConsoleUtils::printNewLine();
    printf("Press Enter to exit OBCViewer");
    (void)getchar();
    ConsoleUtils::clearConsole();
    return 0;

} // End of namespace fs

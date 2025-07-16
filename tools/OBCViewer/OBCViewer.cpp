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

const std::string versionNumber = "1.6";

void printHeader() {
    std::cout << "======================" << std::endl;
    std::cout << "      OBCViewer       " << std::endl;
    std::cout << "======================" << std::endl;
}

void printUsage() {
    printHeader();
    std::cout << "Usage: ./OBCViewer <script.obc>" << std::endl;
    std::cout << "Version - " << versionNumber << std::endl << std::endl;
    std::cout << "Supported games:" << std::endl;
    std::cout << " * Adibou 3" << std::endl;
    std::cout << " * Adi 5" << std::endl;
    std::cout << " * Adibou presente series" << std::endl;
    std::cout << " * Adiboud'chou series" << std::endl;
    std::cout << " * Nathan Vacances series" << std::endl;
    std::cout << " * Le Pays des pierres magiques" << std::endl << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    // Here are listed the strings for OBC itself.
    std::string inputOBC = argv[1];

    #ifdef __unix__
    // List here everything for the Debug Infos.
    std::string username = getlogin();
    #elif __APPLE__
    std::string username = getlogin();
    #endif

    // Check if the input file is an OBC Script.
    fs::path inputScript(inputOBC);
    if (inputScript.extension() != ".obc") {
        std::cerr << "Error: This File is not an OBC Script!" << std::endl;
        return 1;
    }

    // Use the OBC Script for Input
    std::ifstream OBCInput(inputOBC);

    if (!OBCInput) {
        std::cerr << "Error: Unable to find OBC Script." << std::endl;
        return 1;
    }
    
    std::string checkEntrypointOBC;
    char c;
    for (int i = 0; i < 25 && OBCInput.get(c); ++i) {
        checkEntrypointOBC += c;
    }

    // Uses the OBC Copyright MDO as Entrypoint adds automatically also the last four number of the Year.
    // (usually it is 1999, due to OBCEditor it is possible to change this Year so this Change is made so the modified Scripts are always compatible with OBCViewer)
    int number;
    if (sscanf(checkEntrypointOBC.c_str(), "OBC Copyright MDO %d", &number) != 1) {
        printf("Error: Unable to find the number of the Entrypoint!");
        return 1;
    }

    // Rewind the OBC Script back to the beginning
    OBCInput.seekg(0);

    // Open the output file for the OBC Script
    std::ofstream OBCOutput(inputScript.stem().string() + ".txt");

    if (!OBCOutput) {
        printf("Error: Unable to create a text output of the OBC Script");
        return 1;
    }

    // Adds the Date when Output file was created to the Output file
    time_t current_time = time(nullptr);
    char obc_timedate[100];
    strftime(obc_timedate, sizeof(obc_timedate), "%Y-%m-%d %H:%M:%S", localtime(&current_time));

    // Read from input and write to output, keeping track of the offset
    std::streampos offset = OBCInput.tellg();
    while (OBCInput.get(c)) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            OBCOutput.put(c);
            offset = OBCInput.tellg(); // Update the offset after each character is processed
        }
    }

    // Close input & output for OBC Script
    OBCInput.close();
    OBCOutput.close();

    // Create a separate file for Debug Infos
    std::ofstream DebugInfoOutput(inputScript.stem().string() + "_debuginfo.txt");
    if (!DebugInfoOutput) {
        printf("Error: Unable to create Debug Infos file.");
        return 1;
    }

    // Write Debug Infos to the separate file
    DebugInfoOutput << "Debug Infos:" << std::endl;
    DebugInfoOutput << "Output of " << inputScript.stem().string() << ".obc" << " created at " << obc_timedate << std::endl;
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
    printf("%s", fs::absolute(inputScript.stem().string() + ".txt").c_str());
    ConsoleUtils::printNewLine();

    // Exit message for OBCViewer
    ConsoleUtils::printNewLine();
    printf("Press Enter to exit OBCViewer");
    (void)getchar();
    ConsoleUtils::clearConsole();
    return 0;

} // End of namespace fs

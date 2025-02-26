// CTRKViewer is based on OBCViewer

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

#ifdef __unix__
#include <unistd.h>
#endif

namespace fs = std::filesystem;

const std::string versionNumber = "1.0";

void printHeader() {
    std::cout << "======================" << std::endl;
    std::cout << "      CTRKViewer      " << std::endl;
    std::cout << "======================" << std::endl;
}

void printUsage() {
    printHeader();
    std::cout << "Usage: ./CTRKViewer <file.ctrk>" << std::endl;
    std::cout << "Version - " << versionNumber << std::endl << std::endl;
}

void clearConsole() {
    std::cout << "\033[2J\033[H";
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
        std::cerr << "Error: Unable to find CTRK File." << std::endl;
        return 1;
    }

    // Rewind the CTRK Script back to the beginning
    CTRKInput.seekg(0);

    // Open the output file for the CTRK Script
    fs::path inputFile(inputCTRK);
    std::ofstream CTRKOutput(inputFile.stem().string() + ".txt");

    if (!CTRKOutput) {
        std::cerr << "Error: Unable to create a text output of the CTRK Script." << std::endl;
        return 1;
    }

    // Close input & output for CTRK Script
    CTRKInput.close();
    CTRKOutput.close();

    std::cout << "CTRK File (" << argv[1] << ") is now displayable, and the output is saved to " << inputFile.stem().string() << ".txt" << std::endl;

    // Exit message for CTRKViewer
    std::cout << std::endl;
    std::cout << "Press Enter to exit CTRKViewer" << std::endl;
    (void)getchar();
    clearConsole();    
    return 0;

} // End of namespace fs

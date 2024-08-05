#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>
#include <unistd.h>

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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    // Here are listed the strings for OBC itself.
    std::string inputCTRK = argv[1];

    // for clearing the Console after the Program closed.
    std::string clearConsole;

    // List here everything for the Debug Infos.
    std::string username = getlogin();

    #ifdef _WIN32
        clearConsole = "cls"; // Command to clear the console on Windows
    #else
        clearConsole = "clear"; // Command to clear the console on MacOS/Linux
    #endif

    // Check if the input file is an OBC Script.
    std::filesystem::path inputFile(inputCTRK);
    if (inputFile.extension() != ".ctrk") {
        std::cerr << "Error: This File is not an CTRK File!" << std::endl;
        return 1;
    }

    // Use the CTRK File for Input
    std::ifstream CTRKInput(inputCTRK);

    if (!inputFile) {
        std::cerr << "Error: Unable to find CTRK File." << std::endl;
        return 1;
    }

    // Rewind the OBC Script back to the beginning
    CTRKInput.seekg(0);

        // Open the output file for the OBC Script
    std::ofstream CTRKOutput(inputFile.stem().string() + ".txt");

    if (!CTRKOutput) {
        std::cerr << "Error: Unable to create a text output of the OBC Script." << std::endl;
        return 1;
    }

    // Close input & output for OBC Script
    CTRKInput.close();
    CTRKOutput.close();

    std::cout << "CTRK File (" << argv[1] << ") is now displayable, and the output is saved to " << inputFile.stem().string() << ".txt" << std::endl;

    // Exit message for CTRKViewer
    std::cout << std::endl;
    std::cout << "Press Enter to exit CTRKViewer & clear the Console" << std::endl;
    getchar();
    system(clearConsole.c_str());

    return 0;


}
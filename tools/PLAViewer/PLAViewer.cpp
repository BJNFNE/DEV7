#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unistd.h>
#include <algorithm>

namespace fs = std::filesystem;

// Set here the versionNumber
const std::string versionNumber = "1.1";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <savegame.PLA>\n" << std::endl;
        std::cout << "Version - " << versionNumber << "\n" << std::endl;
        std::cout << "Supported games:" << std::endl;
        std::cout << "Land of Magic Stones\n" << std::endl;
        std::cout << "<savegame.PLA>\n\t .PLA savegame to view\n" << std::endl;
        return 1;
    }

    // Here are listed the strings for PLA itself.
    std::string inputPLA = argv[1];

    // for clearing the Console after the Program closed.
    std::string clearConsole;

    #ifdef _WIN32
        clearConsole = "cls"; // Command to clear the console on Windows
    #else
        clearConsole = "clear"; // Command to clear the console on MacOS/Linux
    #endif

    // Convert the extension to lowercase for case-insensitive comparison
    fs::path inputSaveGame(inputPLA);
    std::string extension = inputSaveGame.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension != ".pla") {
        std::cerr << "Error: This File is not an PLA Savegame!\n" << std::endl;
        return 1;
    }

    // Use the PLA Savegame for Input
    std::ifstream PLAInput(inputPLA);

    if (!PLAInput) {
        std::cerr << "Error: Unable to find PLA Savegame." << std::endl;
        return 1;
    }

    // Rewind the PLA Savegame back to the beginning
    PLAInput.seekg(0);

    // Open the output file for the PLA Savegame
    std::ofstream PLAOutput(inputSaveGame.stem().string() + ".txt");

    if (!PLAOutput) {
        std::cerr << "Error: Unable to create a text output of the PLA Savegame." << std::endl;
        return 1;
    }

    // Close input & output for PLA Script
    PLAInput.close();
    PLAOutput.close();

    std::cout << "PLA Savegame (" << argv[1] << ") is now readable." << std::endl;

    // Display the full path of the output file of the PLA Savegame
    std::cout << "\b" << std::endl;
    printf("Output file created at: %s\n", fs::absolute(inputSaveGame.stem().string() + ".txt").c_str());

    // Exit message for PLAViewer
    std::cout << "\b" << std::endl;
    std::cout << "Press Enter to exit PLAViewer.\n" << std::endl;
    (void)getchar();
    int clearConsoleExec = system(clearConsole.c_str());

    return 0;

} // End of namespace fs
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unistd.h>
#include <algorithm>

namespace fs = std::filesystem;

// Set here the versionNumber
const std::string versionNumber = "1.0";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <savegame.PLA>\n" << std::endl;
        std::cerr << "Version - " << versionNumber << "\n" << std::endl;
        printf("Supported games:\n");
        printf("Land of the Magic Stones\n");
        printf("<savegame.PLA>\n\t .PLA savegame to view\n\n");
        return 1;
    }

    // Here are listed the strings for PLA itself.
    std::string inputPLA = argv[1];

    // for clearing the Console after the Program closed.
    std::string clearConsole;

    // List here everything for the Debug Infos.
    std::string username = getlogin();

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

    // Adds the Date when Output file was created to the Output file
    time_t current_time = time(nullptr);
    char PLA_timedate[100];
    strftime(PLA_timedate, sizeof(PLA_timedate), "%Y-%m-%d %H:%M:%S", localtime(&current_time));

    // Read from input and write to output, keeping track of the offset
    std::streampos offset = PLAInput.tellg();
    char c;
    while (PLAInput.get(c)) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            PLAOutput.put(c);
            offset = PLAInput.tellg(); // Update the offset after each character is processed
        }
    }

    // Close input & output for PLA Script
    PLAInput.close();
    PLAOutput.close();

    std::cout << "PLA Savegame (" << argv[1] << ") is now displayable, and the output is saved to " << inputSaveGame.stem().string() << ".txt" << std::endl;

    // Display the full path of the output file of the PLA Savegame
    std::cout << "\b" << std::endl;
    printf("Output file created at: %s\n", fs::absolute(inputSaveGame.stem().string() + ".txt").c_str());

    // Exit message for PLAViewer
    std::cout << "\b" << std::endl;
    std::cout << "Press Enter to exit PLAViewer & clear the Console\n" << std::endl;
    getchar();
    int clearConsoleExecute =  system(clearConsole.c_str());

    return 0;

} // End of namespace fs
#include <iostream>
#include <fstream>
#include <filesystem>
#ifdef __UNIX__
#include <unistd.h>
#endif
#include <algorithm>

#include "common-code/ConsoleUtils.h"

namespace fs = std::filesystem;

char versionNumber[4] = "1.2";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <savegame.PLA>\n" << std::endl;
        printf("Version %s", versionNumber);
        printf("Supported games:\n");
        printf("Land of Magic Stones\n");
        std::cout << "<savegame.PLA>\n\t .PLA savegame to view\n" << std::endl;
        return 1;
    }

    // Here are listed the strings for PLA itself.
    std::string inputPLA = argv[1];

    // Convert the extension to lowercase for case-insensitive comparison
    fs::path inputSaveGame(inputPLA);
    std::string extension = inputSaveGame.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension != ".pla" || extension != ".PLA") {
        fprintf(stderr, "Error: This File is not an PLA Savegame!");
        return 1;
    }

    // Use the PLA Savegame for Input
    std::ifstream PLAInput(inputPLA);

    if (!PLAInput) {
        fprintf(stderr, "Error: Unable to find PLA Savegame.");
        return 1;
    }

    // Rewind the PLA Savegame back to the beginning
    PLAInput.seekg(0);

    // Open the output file for the PLA Savegame
    std::ofstream PLAOutput(inputSaveGame.stem().string() + ".txt");

    if (!PLAOutput) {
        fprintf(stderr, "Error: Unable to create a text output of the PLA Savegame.");
        return 1;
    }

    // Cleanup
    PLAInput.close();
    PLAOutput.close();

    std::cout << "PLA Savegame (" << argv[1] << ") is now readable." << std::endl;

    // Display the full path of the output file of the PLA Savegame
    ConsoleUtils::printNewLine();
    printf("Output file created at: %s\n", fs::absolute(inputSaveGame.stem().string() + ".txt").c_str());

    // Exit message for PLAViewer
    ConsoleUtils::printNewLine();
    printf("Press Enter to exit PLAViewer.\n");
    (void)getchar();
    ConsoleUtils::clearConsole();

    return 0;

} // End of namespace fs
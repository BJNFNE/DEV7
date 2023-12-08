#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unistd.h>

// Set here the versionNumber
const std::string versionNumber = "1.5.1";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <script.obc>\n" << std::endl;
        std::cerr << "Version - " << versionNumber << "\n" << std::endl;
        printf("Supported games:\n");
        printf(" * Adibou 3\n");
        printf(" * Adi 5\n");
        printf(" * Adibou presente series\n");
        printf(" * Adiboud'chou series\n");
        printf(" * Le Pays des pierres magiques\n\n");
        printf("<script.obc>\n\t .obc script to view\n\n");
        printf("Credits:\n");
        printf("BJNFNE (main Developer)\n");
        printf("rzil (BLooperZ) (Thanks for helping out)\n\n");
        return 1;
    }

    // Here are listed the strings for OBC itself.
    std::string inputOBC = argv[1];

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
    std::filesystem::path inputScript(inputOBC);
    if (inputScript.extension() != ".obc") {
        std::cerr << "Error: This File is not an OBC Script!\n" << std::endl;
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

    // Check if OBC Script contains the Entrypoint "OBC Copyright MDO 1999"
    if (checkEntrypointOBC.find("OBC Copyright MDO 1999") != 0) {
        std::cerr << "Error: The Entrypoint in the OBC Script was not found!\n" << std::endl;
        std::cerr << "Maybe you have a new version of OBC? Then please contact BJNFNE on Discord.\n" << std::endl;
        return 1;
    }

    // Rewind the OBC Script back to the beginning
    OBCInput.seekg(0);

    // Open the output file for the OBC Script
    std::ofstream OBCOutput(inputScript.stem().string() + ".txt");

    if (!OBCOutput) {
        std::cerr << "Error: Unable to create a text output of the OBC Script." << std::endl;
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
        std::cerr << "Error: Unable to create Debug Infos file." << std::endl;
        return 1;
    }

    // Write Debug Infos to the separate file
    DebugInfoOutput << "Debug Infos:" << std::endl;
    DebugInfoOutput << "Output of " << inputScript.stem().string() << ".obc" << " created at " << obc_timedate << std::endl;
    DebugInfoOutput << "Created by " << username << std::endl;
    DebugInfoOutput << "Offset (hex): 0x" << std::hex << offset << " hex" << std::dec << std::endl;
    DebugInfoOutput << "Offset (bytes): " << std::scanf << offset << " bytes" << std::dec << std::endl;
    DebugInfoOutput.close();

    std::cout << "OBC Script (" << argv[1] << ") is now displayable, and the output is saved to " << inputScript.stem().string() << ".txt" << std::endl;

    // Display the full path of the output file of the OBC Script
    std::cout << "\b" << std::endl;
    printf("Output file created at: %s\n", std::filesystem::absolute(inputScript.stem().string() + ".txt").c_str());

    // Exit message for OBCViewer
    std::cout << "\b" << std::endl;
    std::cout << "Press Enter to exit OBCViewer & clear the Console" << std::endl;
    getchar();
    system(clearConsole.c_str());

    return 0;
}

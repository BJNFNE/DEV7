#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

// Set here the versionNumber
const std::string versionNumber = "1.4.0";

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <script.obc> <output.txt>\n" << std::endl;
        std::cerr << "Version - " << versionNumber << "\n" << std::endl;
        printf("Supported games:\n");
        printf(" * Adibou 3\n");
        printf(" * Adi 5\n");
        printf(" * Adibou presente series\n");
        printf(" * Adiboud'chou series\n");
        printf(" * Le Pays des pierres magiques\n\n");
        printf("<script.obc>\n\t .obc script to view\n\n");
        printf("<output.txt>\n\tlocate where OBCViewer should store the viewable text of the OBC Script\n\n");
        printf("Credits:\n");
        printf("BJNFNE (main Developer)\n");
        printf("rzil (BLooperZ) (Thanks for helping out)\n\n");
        return 1;
    }

    std::string inputOBC = argv[1];
    std::string outputOBC = argv[2];

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
        std::cerr << "Maybe you have an new version of OBC? Then please contact BJNFNE on Discord.\n" << std::endl;
        return 1;
    }

    // Rewind the OBC Script back to the beginning
    OBCInput.seekg(0);

    // Open the output file for the OBC Script
    std::ofstream OBCOutput(outputOBC);

    if (!OBCOutput) {
        std::cerr << "Error: Unable to create text output of OBC Script." << std::endl;
        return 1;
    }

        // Add Text at the beginning before Entrypoint with "Output of (OBC Script name) was created at then the date (including time)"
    time_t current_time = time(nullptr);
    char obc_timedate[100];
    strftime(obc_timedate, sizeof(obc_timedate), "%Y-%m-%d %H:%M:%S", localtime(&current_time));
    OBCOutput << "Output of " << argv[1] << " was created at " << obc_timedate << std::endl;
    OBCOutput << "\b" << std::endl;

    // Read from input and write to output
    while (OBCInput.get(c)) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            OBCOutput.put(c);
        }
    }

    // Close input & output for OBC Script
    OBCInput.close();
    OBCOutput.close();

    std::cout << "OBC Script (" << argv[1] << ") is now displayable and saved output to " << outputOBC << "" << std::endl;

    // Display the full path of the output file of the OBC Script
    std::cout << "\b" << std::endl;
    printf("Output file created at: %s\n", std::filesystem::absolute(outputOBC).c_str());

    // Exit message for OBCViewer
    std::cout << "\b" << std::endl;
    std::cout << "Press Enter to exit OBCViewer" << std::endl;
    getchar();
    std::cout << "\b" << std::endl;
    exit(0);
}

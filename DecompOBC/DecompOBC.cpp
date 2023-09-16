#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <example_script.obc> <output.txt>" << std::endl;
        std::cout  << "Navigate for the input of the OBC Script to the Full Path including Scriptname.obc\n";
        return 1;
    }

    std::string inputOBC = argv[1];
    std::string outputOBC = argv[2];

    // Use the OBC Script for Input
    std::ifstream OBCInput(inputOBC);

    if (!OBCInput) {
        std::cerr << "Error: Unable to open OBC Script." << std::endl;
        return 1;
    }


    // Open the output file for the OBC Script
    std::ofstream OBCOutput(outputOBC);

    if (!OBCOutput) {
        std::cerr << "Error: Unable to open output of OBC Script." << std::endl;
        return 1;
    }

    // Read from input and write to output
    char c;
    while (OBCInput.get(c)) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            OBCOutput.put(c);
        }
    }

    // Close input & output for OBC Script
    OBCInput.close();
    OBCOutput.close();

    std::cout << "OBC Script has been decompiled and saved to " << outputOBC << "." << std::endl;

    return 0;
}

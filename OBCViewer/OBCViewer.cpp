#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <script.obc> <output.txt>\n" << std::endl;
        printf("Supported games:\n");
        printf(" * Adibou 3\n");
        printf(" * Adi 5\n");
        printf(" * Adibou presente series\n");
        printf(" * Adiboud'chou series\n");
        printf(" * Le Pays des pierres magiques\n");
        printf("\n");
        printf("<script.obc>\n\t .obc script to view\n\n");
        printf("<output.txt>\n\tlocate where OBCViewer should store the viewable text of the OBC Script\n\n");
        return 1;
    }

    std::string inputOBC = argv[1];
    std::string outputOBC = argv[2];

    // Use the OBC Script for Input
    std::ifstream OBCInput(inputOBC);

    if (!OBCInput) {
        std::cerr << "Error: Unable to find OBC Script." << std::endl;
        return 1;
    }

    // Open the output file for the OBC Script
    std::ofstream OBCOutput(outputOBC);

    if (!OBCOutput) {
        std::cerr << "Error: Unable to create text output of OBC Script." << std::endl;
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

    std::cout << "OBC Script (" << argv[1] << ") is viewable and saved output to " << outputOBC  << "" <<std::endl;

    return 0;
}

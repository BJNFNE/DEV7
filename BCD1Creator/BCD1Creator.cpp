#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Ask the user for the file name
    std::cout << "Enter the name of the .BCD1 file: ";
    std::string fileName;
    std::getline(std::cin, fileName);

    // Ask the user for [AppliInfo] details
    std::cout << "Enter [AppliInfo] details:\n";
    std::cout << "name: ";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "nameCD: ";
    std::string nameCD;
    std::getline(std::cin, nameCD);

    std::cout << "pictCD: ";
    std::string pictCD;
    std::getline(std::cin, pictCD);

    std::cout << "MiniEnviVersion: ";
    std::string miniEnviVersion;
    std::getline(std::cin, miniEnviVersion);

    std::cout << "PictureNameR: ";
    std::string pictureNameR;
    std::getline(std::cin, pictureNameR);

    std::cout << "PictureNameC: ";
    std::string pictureNameC;
    std::getline(std::cin, pictureNameC);

    std::cout << "PictureNameN: ";
    std::string pictureNameN;
    std::getline(std::cin, pictureNameN);

    // Open the file for writing
    std::ofstream outputFile(fileName);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    // Write the user-inputted structure to the file
    outputFile << "[AppliInfo]\n";
    outputFile << "name            = " << name << "\n";
    outputFile << "nameCD          = " << nameCD << "\n";
    outputFile << "pictCD          = " << pictCD << "\n";
    outputFile << "MiniEnviVersion = " << miniEnviVersion << "\n";
    outputFile << "PictureNameR    = " << pictureNameR << "\n";
    outputFile << "PictureNameC    = " << pictureNameC << "\n";
    outputFile << "PictureNameN    = " << pictureNameN << "\n";

    // Close the file
    outputFile.close();

    std::cout << "File created successfully: " << fileName << std::endl;

    return 0;
}


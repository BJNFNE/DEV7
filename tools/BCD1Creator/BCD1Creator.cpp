// Information based on b3_appliinfo.obc it is stored in b3_common.stk and is Adibou 3 only.
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Ask the user for the file name
    std::cout << "Enter the name of the .BCD1 file: ";
    std::string fileName;
    std::getline(std::cin, fileName);

    // Ask the user for [AppliInfo] details (Applications only)
    std::cout << "Enter [AppliInfo] details:\n";
    
    std::cout << "Name: ";
    std::string Name;
    std::getline(std::cin, Name);

    std::cout << "CDName: ";
    std::string CDName;
    std::getline(std::cin, CDName);

    std::cout << "PictCD: ";
    std::string PictCD;
    std::getline(std::cin, PictCD);

    std::cout << "MiniEnviVersion: ";
    std::string MiniEnviVersion;
    std::getline(std::cin, MiniEnviVersion);

    std::cout << "PictureNameR: ";
    std::string PictureNameR;
    std::getline(std::cin, PictureNameR);

    std::cout << "PictureNameC: ";
    std::string PictureNameC;
    std::getline(std::cin, PictureNameC);

    std::cout << "PictureNameN: ";
    std::string PictureNameN;
    std::getline(std::cin, PictureNameN);

    // Open the file for writing
    std::ofstream outputBCD1(fileName);

    // Check if the file is opened successfully
    if (!outputBCD1.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    // Write the user-inputted structure to the file
    outputBCD1 << "[AppliInfo]\n";
    outputBCD1 << "Name            = " << Name << "\n";
    outputBCD1 << "CDName          = " << CDName << "\n";
    outputBCD1 << "PictCD          = " << PictCD << "\n";
    outputBCD1 << "MiniEnviVersion = " << MiniEnviVersion << "\n";
    outputBCD1 << "PictureNameR    = " << PictureNameR << "\n";
    outputBCD1 << "PictureNameC    = " << PictureNameC << "\n";
    outputBCD1 << "PictureNameN    = " << PictureNameN << "\n";

    // Close the file
    outputBCD1.close();

    std::cout << "BCD1 file was created successfully: " << fileName << std::endl;

    return 0;
}

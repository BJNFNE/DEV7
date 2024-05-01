// Information based on b3_appliinfo.obc it is stored in b3_common.stk and is Adibou 3 only.
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Ask the user for the file name
    std::cout << "Enter the name of the .BCD1 file: ";
    std::string fileName;
    std::getline(std::cin, fileName);

    // Ask the user to choose between AppliInfo and ENVIINFO
    std::cout << "Choose between [1] AppliInfo or [2] ENVIINFO: ";
    std::string choice;
    std::getline(std::cin, choice);

    // Ask the user for details based on the chosen section
    std::string Name, CDName, PictCD, MiniEnviVersion, Order, PictureNameR, PictureNameC, PictureNameN;

    if (choice == "1") {
        std::cout << "Enter [AppliInfo] details:\n"; // (Applications only!)
        std::cout << "Name: ";
        std::getline(std::cin, Name);
        std::cout << "CDName: ";
        std::getline(std::cin, CDName);
        std::cout << "PictCD: ";
        std::getline(std::cin, PictCD);
        std::cout << "MiniEnviVersion: ";
        std::getline(std::cin, MiniEnviVersion);
       // std::cout << "Order: ";
       // std::getline(std::cin, Order);
        std::cout << "PictureNameR: ";
        std::getline(std::cin, PictureNameR);
        std::cout << "PictureNameC: ";
        std::getline(std::cin, PictureNameC);
        std::cout << "PictureNameN: ";
        std::getline(std::cin, PictureNameN);
    } else if (choice == "2") {
        std::cout << "Enter [ENVIINFO] details:\n";  // (Environment only!)
        std::cout << "Name: ";
        std::getline(std::cin, Name);
        std::cout << "PictCD: ";
        std::getline(std::cin, PictCD);
       // std::cout << "Order: ";
       // std::getline(std::cin, Order);
    } else {
        std::cerr << "Invalid choice. Please enter either '1' or '2'." << std::endl;
        return 1;
    }

    // Open the file for writing
    std::ofstream outputBCD1(fileName);

    // Check if the file is opened successfully
    if (!outputBCD1.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    // Write the user-inputted structure to the file
    if (choice == "1") {
        outputBCD1 << "[AppliInfo]\n"; // (Applications only!)
        outputBCD1 << "Name            = " << Name << "\n";
        outputBCD1 << "CDName          = " << CDName << "\n";
        outputBCD1 << "PictCD          = " << PictCD << "\n";
       // outputBCD1 << "Order           = " << Order << "\n";
        outputBCD1 << "MiniEnviVersion = " << MiniEnviVersion << "\n";
        outputBCD1 << "PictureNameR    = " << PictureNameR << "\n";
        outputBCD1 << "PictureNameC    = " << PictureNameC << "\n";
        outputBCD1 << "PictureNameN    = " << PictureNameN << "\n";
    } else if (choice == "2") {
        outputBCD1 << "[ENVIINFO]\n"; // (Environment only!)
        outputBCD1 << "Name            = " << Name << "\n";
        outputBCD1 << "CDName          = " << CDName << "\n";
    //    outputBCD1 << "Order           = " << Order << "\n";
    }

    // Close the file
    outputBCD1.close();

    std::cout << "BCD1 file was created successfully: " << fileName << std::endl;

    return 0;
}


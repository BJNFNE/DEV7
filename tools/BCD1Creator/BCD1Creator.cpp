/*
BCD1 Files are used for for the detecting the new Application, And add it to the Vulkan from where you can choose the Application to enter.

Information based on b3_appliinfo.obc is stored in b3_common.stk  (Adibou 3 only).
Information comes from b3_cdmanager.ini stored in b3_common.itk (Adibou 3 only).

:Functions:
name here the Name of the Application gets displayed.
nameCD shows your the Name of the Disc, for the Window thats shows up if the Disc is not inserted.
pictCD is for using the Image (.img) in the Menu where you can select your Application.
MiniEnviVersion for set what is the Minimum version of Adibou 3 is required to use the Application. 
(If an newer Application is being added to an older version Adibou 3 Environment then an message is shown to let the User know that they have to update the Environment.)
PictureNameR for which picture should used for the Right.
PictureNameC for which picture should used for the Corner.
PictureNameN for which picture should used for the Middle?
CDDetected checks if the CD was detected correctly, also checks for SecuROM.
Order is to give Adibou 3 the the position where the Application should be shown in the Vulkan.


[mask]
envi=benxxD???.bcd?
appli=b????D???.bcd?

*/

#include <iostream>
#include <fstream>
#include <string>

void exampleBCD1Names() {

    std::cout << "Example BCD1 Filenames which were detected by Adibou 3\n" << std::endl;

    std::cout << "French: " << "\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << " - Le pays d'Adibou [benxxf300.bcd1]\n" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Le Royaume des Murmures (Lecture 4-5) [BFR45F300.BCD1]\n" << std::endl;
    std::cout << " - Le Royaume Méli-Mélo (Calcul 4-5 ans) [BMA45F300.BCD1]\n" << std::endl;
    std::cout << " - L'île volante (Sciences 4-7 ans) [bsc47F310.bcd1]" << std::endl;

    std::cout << "German: " << "\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << " - Das Zauberland von Adiboo [benxxd300.bcd1]\n" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Die Stadt Wiwawort (Wörter 5-6 Jahre) [BFR56D300.BCD1]\n" << std::endl;
    std::cout << " - Die Stadt Plusminus (Zahlen 5-6 Jahre) [BMA56D300.BCD1]\n" << std::endl;
    std::cout << " - Das Tal Wortwörtlich (Im Leseland 6-7 Jahre)[BFR67D300.BCD1]\n" << std::endl;
    std::cout << " - Das Tal Zählmal (Im Rechenland 6-7 Jahre) [BMA67D300.BCD1]\n" << std::endl;
    std::cout << " - Das Königreich Hocus Pocus (Englisch 4-7 Jahre) [blg47D310.bcd1]\n" << std::endl;
    std::cout << " - Das schwebende Land (Natur & Technik 4-7) [bsc47D310.bcd1]\n" << std::endl;

    std::cout << "English:\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Word-by-Word City (Reading 5-6 years) [bfr56a300.bcd1]\n" << std::endl;
    std::cout << " - More-or-Less City (Maths 5-6 years) [BMA56A300.BCD1]\n" << std::endl;
    std::cout << " - The Mysterious Music Machine 4-7 years [bmu47A310.bcd1]\n" << std::endl;

    std::cout << "Russian:\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Ãîðîä Íåðàâåíñòâ (Ñ÷åò 5-6 ëåò) [bma56F300.bcd1]\n" << std::endl;
    std::cout << " - Ñ÷åòíàÿ äîëèíà (Ñ÷åò 6-7 ëåò) [bma67F300.bcd1]\n" << std::endl;
    std::cout << " - Çàáûòàÿ ñòðàíà (Íàóêè, 4-7 ëåò) [bsc47F310.bcd1]\n" << std::endl;
    std::cout << " - Çàãàäî÷íàÿ ìóçûêàëüíàÿ ìàøèíà (Ìóçûêà, 4-7 ëåò) [bmu47A310.bcd1]\n" << std::endl;
    std::cout << " - Êîðîëåâñòâî Ôîêóñ-Ïîêóñ (Àíãëèéñêèé, 4-7 ëåò) [blg47F310.bcd1]\n" << std::endl;

    std::cout << "Dutch:\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << " - Het Land van Adiboo [benxxa300.bcd1]\n" << std::endl;
    std::cout << "Application:\b" << std::endl;

    return;
}

void printHeader() {
    const std::string versionNumber = "0.1.1";

    std::cout << "==========================" << std::endl;
    std::cout << " BCD1Creator ver. " << versionNumber << std::endl;
    std::cout << "==========================" << std::endl;
}

int main() {
    printHeader();
    std::cout << "\b" << std::endl;
    exampleBCD1Names();
    std::cout << "\b" << std::endl;
    // Ask the user for the BCD1 file name
    std::cout << "Enter the Filename of the Game which you wanna modify: " << std::endl;
    std::string fileName;
    std::getline(std::cin, fileName);

    // Ask the user to choose between AppliInfo and ENVIINFO
    std::cout << "Choose between [1] AppliInfo or [2] ENVIINFO: ";
    std::string choice;
    std::getline(std::cin, choice);

    // Ask the user for details based on the chosen section
    std::string Name, CDName, PictCD, MiniEnviVersion, Order, PictureNameR, PictureNameC, PictureNameN, IDFile, CDDetected;

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
        // std::cout << "IDFile: ";
        // std::getline(std::cin, IDFile);
        // std::cout << "CDDetected: ";
        // std::getline(std::cin, CDDetected);
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
      //  outputBCD1 << "IDFile          = " << IDFile << "\n";
      //  outputBCD1 << "CDDetected      = " << CDDetected << "\n";
    } else if (choice == "2") {
        outputBCD1 << "[ENVIINFO]\n"; // (Environment only!)
        outputBCD1 << "Name            = " << Name << "\n";
        outputBCD1 << "CDName          = " << CDName << "\n";
    // outputBCD1 << "Order           = " << Order << "\n";
    // outputBCD1 << "IDFile          = " << IDFile << "\n";
    // outputBCD1 << "CDDetected      = " << CDDetected << "\n";
    }

    // Close the file
    outputBCD1.close();

    std::cout << "BCD1 file was created successfully: " << fileName << std::endl;

    return 0;
}

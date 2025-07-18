/*
BCD1 Files are used for for the detecting the new Application, And add it to the Vulkan from where you can choose the Application to enter.

Information based on b3_appliinfo.obc is stored in b3_common.stk (Adibou 3 only).

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

This Information comes from b3_cdmanager.ini (Adibou 3 only).
[mask]
envi=benxxD???.bcd?
appli=b????D???.bcd?

Requirements:
The first B stands for Adibou
After that the secound two letters are for what type of Application it is (MU = Music FR = Language = MA = Math SC = Sciences LG = Hocus Pocus).
Then the Year of the Age.
The last letter is the Language (F = French/Russian, E = English, D = German/Dutch)
The last 3 numbers are for the version number.
*/

#include <iostream>
#include <fstream>

#include "common-code/ConsoleUtils.h"

#ifdef _WIN32
#include <windows.h> // For setting console encoding
#endif

void exampleBCD1Names() {
    std::cout << "Example BCD1 Filenames which were detected by Adibou 3\n" << std::endl;

    std::cout << "Français:" << "\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << " - Le pays d'Adibou [benxxf300.bcd1]\n" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Le Royaume des Murmures (Lecture 4-5) [BFR45F300.BCD1]\n" << std::endl;
    std::cout << " - Le Royaume Méli-Mélo (Calcul 4-5 ans) [BMA45F300.BCD1]\n" << std::endl;
    std::cout << " - L'île volante (Sciences 4-7 ans) [bsc47F310.bcd1]\n" << std::endl;

    std::cout << "Deutsch:" << "\b" << std::endl;
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

#ifdef _WIN32
    // Set code page to UTF-8 (65001) for universal character support
    SetConsoleCP(65001);          // Set input code page to UTF-8
    SetConsoleOutputCP(65001);    // Set output code page to UTF-8
#endif

    std::cout << "русский:\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Король Смирности (Чтение 5-6 лет) [bma56F300.bcd1]\n" << std::endl;
    std::cout << " - Сказочная долина (Чтение 6-7 лет) [bma67F300.bcd1]\n" << std::endl;
    std::cout << " - Загадочная страна (Науки, 4-7 лет) [bsc47F310.bcd1]\n" << std::endl;
    std::cout << " - Занимательная музыкальная машинка (Музыка, 4-7 лет) [bmu47A310.bcd1]\n" << std::endl;
    std::cout << " - Королевство Фокус-Покус (Английский, 4-7 лет) [blg47F310.bcd1]\n" << std::endl;

#ifdef _WIN32
    // Optionally reset to default code page (optional)
    SetConsoleCP(437);           // Set input code page back to default (optional)
    SetConsoleOutputCP(437);     // Set output code page back to default (optional)
#endif

    std::cout << "Nederlands:\b" << std::endl;
    std::cout << "Environment:\b" << std::endl;
    std::cout << " - Het Land van Adiboo [benxxa300.bcd1]\n" << std::endl;
    std::cout << "Application:\b" << std::endl;
    std::cout << " - Rekenen 5-6 jaar [bma56a300.bcd1]\n" << std::endl;
    return;
}

void printHeader() {
    const std::string versionNumber = "0.1.1";

    std::cout << "==========================" << std::endl;
    std::cout << " BCD1Creator ver. " << versionNumber << std::endl;
    std::cout << "==========================" << std::endl;
}

int main(int argc, const char **argv) {
    printHeader();
    ConsoleUtils::printNewLine();
    exampleBCD1Names();
    ConsoleUtils::printNewLine();
    // Ask the user for the BCD1 file name
    std::cout << "Enter the Filename of the Game which you wanna modify: " << std::endl;
    std::string fileName;
    getline(std::cin, fileName);

    // Ask the user to choose between AppliInfo and ENVIINFO
    std::cout << "Choose between [1] AppliInfo or [2] ENVIINFO: ";
    std::string choice;
    getline(std::cin, choice);

    // Ask the user for details based on the chosen section
    std::string Name, CDName, PictCD, MiniEnviVersion, Order, PictureNameR, PictureNameC, PictureNameN, IDFile, CDDetected;

    if (choice == "1") {
        std::cout << "Enter [AppliInfo] details:\n"; // (Applications only!)
        std::cout << "Name: ";
        getline(std::cin, Name);
        std::cout << "CDName: ";
        getline(std::cin, CDName);
        std::cout << "PictCD: ";
        getline(std::cin, PictCD);
        std::cout << "MiniEnviVersion: ";
        getline(std::cin, MiniEnviVersion);
        // std::cout << "Order: ";
        // getline(std::cin, Order);
        std::cout << "PictureNameR: ";
        getline(std::cin, PictureNameR);
        std::cout << "PictureNameC: ";
        getline(std::cin, PictureNameC);
        std::cout << "PictureNameN: ";
        getline(std::cin, PictureNameN);
    }
    else if (choice == "2") {
        std::cout << "Enter [ENVIINFO] details:\n";  // (Environment only!)
        std::cout << "Name: ";
        getline(std::cin, Name);
        std::cout << "PictCD: ";
        getline(std::cin, PictCD);
        // std::cout << "Order: ";
        // getline(std::cin, Order);
        // std::cout << "IDFile: ";
        // getline(std::cin, IDFile);
        // std::cout << "CDDetected: ";
        // getline(std::cin, CDDetected);
    }
    else {
        fprintf(stderr, "Invalid choice. Please enter either '1' or '2'.\n");
        return 1;
    }

    // Open the file for writing
    std::ofstream outputBCD1(fileName);

    // Check if the file is opened successfully
    if (!outputBCD1.is_open()) {
        fprintf(stderr, "Error opening file for writing.\n");
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
        // outputBCD1 << "IDFile          = " << IDFile << "\n";
        // outputBCD1 << "CDDetected      = " << CDDetected << "\n";
    }
    else if (choice == "2") {
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
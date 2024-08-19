#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#define SLEEP_COMMAND "ping -n 2 127.0.0.1 > nul"
#define DEV7_MUTEX_LAUNCH "DEV7_INSTANCE_MUTEX"
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#define SLEEP_COMMAND "sleep 2"
#define DEV7_MUTEX_LAUNCH "/tmp/DEV7_INSTANCE_MUTEX"
#endif

bool fileExists(const std::string& filename) {
#ifdef _WIN32
    return _access(filename.c_str(), 0) == 0;
#else
    struct stat buffer;
    return stat(filename.c_str(), &buffer) == 0;
#endif
}

void printHeader() {
    const std::string versionNumber = "0.1.0";

    std::cout << "=========================" << std::endl;
    std::cout << " DEV7Launcher ver. " << versionNumber << std::endl;
    std::cout << "=========================" << std::endl;
}

void clearConsole() {
    std::cout << "\033[2J\033[H";
    return;
}

bool isDEV7Running() {
#ifdef _WIN32
    HANDLE mutex = CreateMutex(NULL, TRUE, DEV7_MUTEX_LAUNCH);
    if (mutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(mutex);
        return true;
    }
#else
    int fd = open(DEV7_MUTEX_LAUNCH, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        return true;
    }
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        close(fd);
        return true;
    }
#endif
    return false;
}

void launchCommand(const std::string& command) {
    #ifdef _WIN32
        system(command.c_str());
    #else
        std::string wineCommand = "wine " + command;
        int result = system(wineCommand.c_str());
    #endif
   int sleepcmd = system(SLEEP_COMMAND);
}

void modifyMDOIni() {
    #ifdef _WIN32
        int result = system("notepad mdo.ini");
    #else
        std::string modifyMDOIni = "nano mdo.ini";
        int result = system(modifyMDOIni.c_str());
    #endif
}

void showMSGDef() {
    #ifdef _WIN32
        int msgDEF = system("notepad msg.def");
    #else
        std::string modifyMSGDef = "nano msg.def";
        int msgDEF = system(modifyMSGDef.c_str());
    #endif
}

void modifyMDODbg() {
    std::string mdo_dbg = "MDO.DBG";

    if (!fileExists(mdo_dbg)) {
        std::cout << "Error: " << mdo_dbg << " not found in the directory.\n" << std::endl;
        std::cout << "Press Enter to exit DEV7Launcher" << std::endl;
        getchar();
        clearConsole();
        return;
    }

    #ifdef _WIN32
        int mdoDBG = system("notepad MDO.DBG");
    #else
        std::string modifyMDODbg = "nano MDO.dbg";
        int mdoDBG = system(modifyMDODbg.c_str());
    #endif
}

void showTraceTXT() {
    #ifdef _WIN32
        int traceTXT = system("notepad Trace.txt");
    #else
        std::string showTraceTXT = "nano Trace.txt";
        int traceTXT = system(showTraceTXT.c_str());
    #endif
}

void modifyAdibou3Ini() {

     // Check if Adibou3.ini exists
    if (!std::filesystem::exists("Adibou3.ini")) {
        std::cout << "Error: This directory does not seem to be an Adibou 3 game directory.\n" << std::endl;
        std::cout << "Press Enter to exit DEV7Launcher" << std::endl;
        getchar();
        clearConsole();
        return;
    }

    // This an Workaround for this Function to load Adibou3.ini into the Editors
    // WORKAROUND: rename ADIBOU3.INI to Adibou3.ini so it will be read by the Editors as Adibou3.ini to avoid problems being loaded.

#ifdef _WIN32
  if (!std::filesystem::exists("Adibou3.ini")) {
    system("ren ADIBOU3.INI Adibou3.ini");
  }
    system("notepad Adibou3.ini");
#else
  if (!std::filesystem::exists("Adibou3.ini")) {
     int move_adibou3 = system("mv ADIBOU3.INI Adibou3.ini");
  }
   int nano_adibou3 = system("nano Adibou3.ini");
#endif
}

void modifyAdi5Ini() {

     // Check if Data/ADI5.ini exists
    if (!std::filesystem::exists("Data/ADI5.ini")) {
        std::cout << "Error: This directory does not seem to be an Adi 5 game directory.\n" << std::endl;
        std::cout << "Press Enter to exit DEV7Launcher" << std::endl;
        getchar();
        clearConsole();
        return;
    }

    #ifdef _WIN32
        int adi5ini = system("notepad Data/ADI5.ini");
    #else
        std::string modifyAdi5Ini = "nano Data/ADI5.ini";
        int adi5ini = system(modifyAdi5Ini.c_str());
    #endif
}

void openLicenceFile() {
    std::string licenseFile = "Lizenzvereinbarung.txt";
    std::string warrantyFile = "garantie.txt";
    std::string lisezMoiFile = "LISEZ MOI.txt";
    bool foundLicense = std::filesystem::exists(licenseFile);
    bool foundWarranty = std::filesystem::exists(warrantyFile);
    bool foundLisezMoi = std::filesystem::exists(lisezMoiFile);

    if (foundLicense || foundWarranty || foundLisezMoi) {
        std::string filename;
        if (foundLicense) {
            filename = licenseFile;
        } else if (foundWarranty) {
            filename = warrantyFile;
        } else {
            filename = lisezMoiFile;
        }

#ifdef _WIN32
        system(("notepad.exe " + filename).c_str());
        std::cout << "Please wait a few moments to open the Licence for you.\n" << std::endl;
#else
        int open = system(("open " + filename).c_str());
        std::cout << "Please wait a few moments to open the Licence for you.\n" << std::endl;
#endif

    } else {
        std::cout << "License or warranty file not found.\n" << std::endl;
    }
}

void runUNINST() {
    std::string uninst = "UNINST.EXE";

    if (!fileExists(uninst)) {
        std::cout << "Error: " << uninst << " not found in directory.\n" << std::endl;
        return;
    }
#ifdef _WIN32
    system("UNINST.EXE");
    std::cout << "Follow the Instructions to process the uninstallation.\n" << std::endl;
#else
    if (system("wine UNINST.EXE") != 0) {
    std::cout << "Uninstaller has been started over wine, Follow the Instructions to process the uninstallation.\n" << std::endl;
    }
#endif
}

void Ed4Intro() {
    std::string Ed4IntroEXE = "Ed4Intro.exe";

     // Check if Ed4Intro.exe exists
    if (!std::filesystem::exists("Ed4Intro.exe")) {
        std::cout << "Error: This directory does not seem to be an Le Pays des pierres magiques game directory.\n" << std::endl;
        return;
    }
#ifdef _WIN32
    system("Ed4Intro.exe");
#else
    if (system("wine Ed4Intro.exe") != 0) {
    }
#endif
}

void startLoader7Normal() {
    if (fileExists("LoaderMDO.exe"))
        std::cout << "LoaderMDO.exe found. Starting LoaderMDO.exe..." << std::endl, launchCommand("LoaderMDO.exe");
    else if (fileExists("LoaderMDO.exe"))
        std::cout << "LoaderMDO.exe found. Starting LoaderMDO.exe over wine..." << std::endl, launchCommand("wine LoaderMDO.exe");
    else if (fileExists("Adibou3.EXE"))
        std::cout << "Adibou3.EXE found. Starting Adibou3.EXE..." << std::endl, launchCommand("Adibou3.EXE");
    else if (fileExists("Adibou3.exe"))
        std::cout << "Adibou3.exe found. Starting Adibou3.exe over wine..." << std::endl, launchCommand("wine adibou3.exe");
    else if (fileExists("ADI5.EXE"))
        std::cout << "ADI5.EXE found. Starting ADI5.EXE..." << std::endl, launchCommand("ADI5.EXE");
    else if (fileExists("ADI5.exe"))
        std::cout << "ADI5.exe found. Starting ADI5.exe over wine..." << std::endl, launchCommand("wine ADI5.exe");
    else if (fileExists("Loader7.exe"))
        std::cout << "Loader7.exe found. Starting ADI5.EXE..." << std::endl, launchCommand("Loader7.exe");
    else if (fileExists("Loader7.exe"))
        std::cout << "Loader7.exe found. Starting Loader7.exe over wine..." << std::endl, launchCommand("wine Loader7.exe");
    else
        std::cout << "None of the executables found. \nPlease make sure you have the exe in the same Directory as the Launcher." << std::endl;
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::steady_clock::now(); // Record the start time
    
    int choice;
    bool usedLoaderOrDev7VM = false; // Flag to track if Loader7.exe or Dev7VM.EXE was used

    if (isDEV7Running()) {
        std::cout << "A DEV7 client is already running, cannot handle more than one DEV7 client.\n" << std::endl;
        getchar();
        clearConsole();
        return 1;
    }

    bool Loader7Exists = (std::ifstream("loader7.exe").good() || std::ifstream("LOADER7.EXE").good()) || std::ifstream("Loader7.exe").good();
    bool Dev7VMExists = fileExists("Dev7VM.EXE");

    // execute here the printHeader() to display the Header (Program name with versionNumber)
    printHeader();

    if (Loader7Exists && Dev7VMExists) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Start Dev7VM with Debug Menu\n";
        std::cout << "2. Start Dev7VM Normal\n";
        std::cout << "3. Start loader7 with Debug Menu\n";
        std::cout << "4. Start loader7 Normal\n";
        std::cout << "5. Modify mdo.ini\n";
        std::cout << "7. Show Trace.txt (contains the output of Trace window from Debug Menu)\n";
        std::cout << "8. Modify mdo.dbg\n";
        std::cout << "9. Launch Parentsection (Adibou 3 only)\n";
        std::cout << "10. Modify Adibou3.ini (Adibou 3 only)\n";
        std::cout << "11. Run Uninstaller (UNINST.EXE)\n";
        std::cout << "12. Start Le pays des Pierres magiques Intro\n";
        std::cout << "13. Modify Adi5.ini (Adi 5 only)\n";
        std::cout << "14. Open Licence Agreement\n";
        std::cout << "15. Open MSG.DEF\n";
    } else if (Loader7Exists) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Start loader7 with Debug Menu\n";
        std::cout << "2. Start loader7 Normal\n";
        std::cout << "3. Modify mdo.ini\n";
        std::cout << "4. Show Trace.txt (contains the output of Trace window from Debug Menu)\n";
        std::cout << "5. Modify mdo.dbg\n";
        std::cout << "6. Launch Parentsection (Adibou 3 only)\n";
        std::cout << "7. Modify Adibou3.ini (Adibou 3 only)\n";
        std::cout << "8. Run Uninstaller\n";
        std::cout << "9. Start Le pays des Pierres magiques Intro\n";
        std::cout << "10. Modify Adi5.ini (Adi 5 only)\n";
        std::cout << "11. Open Licence Agreement\n";
        std::cout << "12. Open MSG.DEF\n";
    } else if (Dev7VMExists) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Start Dev7VM with Debug Menu\n";
        std::cout << "2. Start Dev7VM Normal\n";
        std::cout << "3. Modify mdo.ini\n";
        std::cout << "4. Show Trace.txt (contains the output of Trace window from Debug Menu)\n";
        std::cout << "5. Modify mdo.dbg\n";
        std::cout << "6. Launch Parentsection (Adibou 3 only)\n";
        std::cout << "7. Modify Adibou3.ini (Adibou 3 only)\n";
        std::cout << "8. Run Uninstaller (UNINST.EXE)\n";
        std::cout << "9. Start Le pays des Pierres magiques Intro\n";
        std::cout << "10. Modify Adi5.ini (Adi 5 only)\n";
        std::cout << "11. Open Licence Agreement\n";
        std::cout << "12. Open MSG.DEF\n";
    } else {
        std::cout << "Error: Dev7VM.EXE or Loader7.exe is not found in the Game directory. Launcher terminated." << std::endl;
        std::cout << "Press Enter to exit." << std::endl;
        getchar();
        clearConsole();
        return 1;
    }

    std::cin >> choice;
    std::cout << "\n";

switch(choice) {
    case 1:
        if (Loader7Exists) {
            launchCommand("Loader7.exe -break");
            usedLoaderOrDev7VM = true;
        } else if (Dev7VMExists) {
            launchCommand("Dev7VM.exe -break");
            usedLoaderOrDev7VM = true;
        }
        break;
    case 2:
        if (Loader7Exists) {
            startLoader7Normal();
            usedLoaderOrDev7VM = true;
        } else if (Dev7VMExists) {
            launchCommand("Dev7VM.exe");
            usedLoaderOrDev7VM = true;
        }
        break;
    case 3:
        modifyMDOIni();
        usedLoaderOrDev7VM = false;
        break;
    case 4:
        showTraceTXT();
        usedLoaderOrDev7VM = false;
        break;
    case 5:
        modifyMDODbg();
        usedLoaderOrDev7VM = false;
        break;
    case 6:
        if (Loader7Exists) {
            launchCommand("Loader7.exe -obc='B3_ParentLaunch'");
            usedLoaderOrDev7VM = true;
        } else if (Dev7VMExists) {
            launchCommand("Dev7VM.EXE -obc='B3_ParentLaunch'");
            usedLoaderOrDev7VM = true;
        }
        break;
    case 7:
        modifyAdibou3Ini();
        usedLoaderOrDev7VM = false;
        break;
    case 8:
        runUNINST();
        usedLoaderOrDev7VM = false;
        break;
    case 9:
        Ed4Intro();
        usedLoaderOrDev7VM = true;
        break;
    case 10:
        modifyAdi5Ini();
        usedLoaderOrDev7VM = false;
        break;
    case 11:
        openLicenceFile();
        usedLoaderOrDev7VM = false;
        break;
    case 12:
        showMSGDef();
        usedLoaderOrDev7VM = false;
        break;
    default:
        std::cout << "Invalid choice. Please choose a valid option.\n" << std::endl;
        usedLoaderOrDev7VM = false;
        break;
}

auto end = std::chrono::steady_clock::now(); // Record the end time
auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start); // Calculate elapsed time in seconds

if (usedLoaderOrDev7VM) {
    clearConsole();
}

std::cout << "Total playtime: " << elapsed.count() << " seconds." << std::endl;

std::cout << "Would you like to restart DEV7Launcher? (y/n): ";
char restartChoice;
std::cin >> restartChoice;

if (restartChoice == 'y' || restartChoice == 'Y') {
    std::cout << "Delete temp files of DEV7Launcher..." << std::endl;
    // TODO: improve Windows workaround for delete temp files
    //#ifdef _WIN32
    //system("del /tmp/DEV7_INSTANCE_MUTEX");
    //#endif
    int delete_mutex = system("rm /tmp/DEV7_INSTANCE_MUTEX");
    clearConsole();  // Clear the console before restarting
    main(argc, argv);  // Restart the launcher by calling main again
}

if (restartChoice == 'n' || restartChoice == 'N') {

    clearConsole();

}

return 0;

}

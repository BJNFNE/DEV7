#include <iostream>
#include <fstream>
#include <filesystem>

#include "common-code/ConsoleUtils.h"
#include "common-code/TaskExecution.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#define SLEEP_COMMAND_WIN "ping -n 2 127.0.0.1 > nul"
#define DEV7_MUTEX_LAUNCH_WIN "%temp%/DEV7_INSTANCE_MUTEX"
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#define SLEEP_COMMAND_UNIX "sleep 2"
#define DEV7_MUTEX_LAUNCH_UNIX "/tmp/DEV7_INSTANCE_MUTEX"
#endif

// Defines
#define READ_WRITE_PERMISSION 0666

// Namespaces
namespace fs = std::filesystem;

bool fileExists(const std::string& filename) {
#ifdef _WIN32
    return _access(filename.c_str(), 0) == 0;
#else
    struct stat buffer;
    return stat(filename.c_str(), &buffer) == 0;
#endif
}

void printHeader() {
    const std::string versionNumber = "1.2.0";

    printf("=========================\n");
    std::cout << " DEV7Launcher ver. " << versionNumber << std::endl;
    printf("=========================\n");
}

bool isDEV7Running() {
#ifdef _WIN32
    HANDLE mutex = CreateMutex(NULL, TRUE, DEV7_MUTEX_LAUNCH_WIN);
    if (mutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(mutex);
        return true;
    }
#else
    int fd = open(DEV7_MUTEX_LAUNCH_UNIX, O_CREAT | O_RDWR, READ_WRITE_PERMISSION);
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
        int sleepCmdUnix = system(SLEEP_COMMAND_UNIX);
    #endif
}

void modifyMDOIni() {
    #ifdef _WIN32
        int mdoIni = system("notepad mdo.ini");
    #else
        std::string modifyMDOIni = "nano mdo.ini";
        int mdoIni = system(modifyMDOIni.c_str());
    #endif
}

void showMSGDef() {
    #ifdef _WIN32
        int showMsgDef = system("notepad msg.def");
    #else
        std::string showMSGDef = "nano msg.def";
        int showMsgDef = system(showMSGDef.c_str());
    #endif
}

void modifyMDODbg() {
    std::string mdo_dbg = "MDO.DBG";

    if (!fileExists(mdo_dbg)) {
        std::cout << "Error: " << mdo_dbg << " not found in the directory.\n" << std::endl;
        TaskExecution::pressEnterToExit();
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
    if (!fs::exists("Adibou3.ini")) {
        std::cout << "Error: This directory does not seem to be an Adibou 3 game directory.\n" << std::endl;
        TaskExecution::pressEnterToExit();
        return;
    }

    // This an Workaround for this Function to load Adibou3.ini into the Editors
    // WORKAROUND: rename ADIBOU3.INI to Adibou3.ini so it will be read by the Editors as Adibou3.ini to avoid problems being loaded.
#ifdef _WIN32
  if (!fs::exists("Adibou3.ini")) {
    int moveAdibou3Ini = system("ren ADIBOU3.INI Adibou3.ini");
  }
   int editAdibou3Ini = system("notepad Adibou3.ini");
#else
  if (!fs::exists("Adibou3.ini")) {
     int moveAdibou3Ini = system("mv ADIBOU3.INI Adibou3.ini");
  }
   int editAdibou3Ini = system("nano Adibou3.ini");
#endif
}

void modifyAdi5Ini() {

     // Check if Data/ADI5.ini exists
    if (!fs::exists("Data/ADI5.ini")) {
        printf("Error: This directory does not seem to be an Adi 5 game directory.\n");
        TaskExecution::pressEnterToExit();
        return;
    }

    #ifdef _WIN32
        int editAdi5Ini = system("notepad Data/ADI5.ini");
    #else
        std::string modifyAdi5Ini = "nano Data/ADI5.ini";
        int editAdi5Ini = system(modifyAdi5Ini.c_str());
    #endif
}

void openLicenceFile() {
    std::string licenseFile = "Lizenzvereinbarung.txt"; // German
    std::string warrantyFile = "garantie.txt"; // English
    std::string lisezMoiFile = "LISEZ MOI.txt"; // French
    bool foundLicense = fs::exists(licenseFile);
    bool foundWarranty = fs::exists(warrantyFile);
    bool foundLisezMoi = fs::exists(lisezMoiFile);

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
        int open = system(("notepad.exe " + filename).c_str());
        printf("Please wait a few moments to open the Licence for you.\n");
#else
        int open = system(("open " + filename).c_str());
        printf("Please wait a few moments to open the Licence for you.\n");
#endif

    } else {
        printf("License or warranty file not found.\n");
    }
}

void runUNINST() {
    std::string uninst = "UNINST.EXE";

    if (!fileExists(uninst)) {
        std::cout << "Error: " << uninst << " not found in directory.\n" << std::endl;
        return;
    }
#ifdef _WIN32
    int Uninstaller = system("UNINST.EXE");
    std::cout << "Follow the Instructions to process the uninstallation.\n" << std::endl;
#else
    if (system("wine UNINST.EXE") != 0) {
    printf("Uninstaller has been started over wine, Follow the Instructions to process the uninstallation.\n");
    }
#endif
}

void Ed4Intro() {
    std::string Ed4IntroEXE = "Ed4Intro.exe";

     // Check if Ed4Intro.exe exists
    if (!fs::exists("Ed4Intro.exe")) {
        printf("Error: This directory does not seem to be an Le Pays des pierres magiques game directory.\n");
        return;
    }
#ifdef _WIN32
    int Ed4Intro = system("Ed4Intro.exe");
#else
    int Ed4Intro = system("wine Ed4Intro.exe");
#endif
}

void startGameExecutable() { // TODO: Function refactor/rework has to be done from scratch
    if (fileExists("LoaderMDO.exe"))
        std::cout << "LoaderMDO.exe found. Starting LoaderMDO.exe..." << std::endl, launchCommand("LoaderMDO.exe");
    else if (fileExists("LoaderMDO.exe"))
        std::cout << "LoaderMDO.exe found. Starting LoaderMDO.exe over wine..." << std::endl, launchCommand("wine LoaderMDO.exe");
    else if (fileExists("Adibou3.EXE"))
        std::cout << "Adibou3.EXE found. Starting Adibou3.EXE..." << std::endl, launchCommand("Adibou3.EXE");
    else if (fileExists("Adibou3.exe"))
        std::cout << "Adibou3.exe found. Starting Adibou3.exe over wine..." << std::endl, launchCommand("wine adibou3.exe");
    else if (fileExists("adiboo3.exe"))
        std::cout << "adiboo3.exe found. Starting adiboo3.exe..." << std::endl, launchCommand("adiboo3.exe");
    else if (fileExists("adiboo3.exe"))
        std::cout << "adiboo3.exe found. Starting adiboo3.exe over wine..." << std::endl, launchCommand("wine adiboo3.exe");
    else if (fileExists("ADI5.EXE"))
        std::cout << "ADI5.EXE found. Starting ADI5.EXE..." << std::endl, launchCommand("ADI5.EXE");
    else if (fileExists("ADI5.exe"))
        std::cout << "ADI5.exe found. Starting ADI5.exe over wine..." << std::endl, launchCommand("wine ADI5.exe");
    else if (fileExists("Loader7.exe"))
        std::cout << "Loader7.exe found. Starting ADI5.EXE..." << std::endl, launchCommand("Loader7.exe");
    else if (fileExists("Loader7.exe"))
        std::cout << "Loader7.exe found. Starting Loader7.exe over wine..." << std::endl, launchCommand("wine Loader7.exe");
    else
        printf("None of the executables found. \nPlease make sure you have the exe in the same Directory as the Launcher.");
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::steady_clock::now(); // Record the start time
    
    int choice;
    bool usedLoader7OrDev7VM = false; // Flag to track if Loader7.exe or Dev7VM.EXE was used

    if (isDEV7Running()) {
        printf("A DEV7 client is already running, cannot handle more than one DEV7 client.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    bool Loader7Exists = (std::ifstream("loader7.exe").good() || std::ifstream("LOADER7.EXE").good()) || std::ifstream("Loader7.exe").good();
    bool Dev7VMExists = fileExists("Dev7VM.EXE");

    // execute here the printHeader() to display the Header (Program name with versionNumber)
    printHeader();

    if (Loader7Exists && Dev7VMExists) {
        printf("Choose an option:\n");
        printf("1. Start Dev7VM with Debug Menu/Windowed mode\n");
        printf("2. Start Dev7VM in Fullscreen mode\n");
        printf("3. Start loader7 with Debug Menu/Windowed mode\n");
        printf("4. Start loader7 in Fullscreen mode\n");
        printf("5. Modify mdo.ini\n");
        printf("7. Show Trace.txt (contains the output of Trace window from Debug Menu)\n");
        printf("8. Modify mdo.dbg\n");
        printf("9. Launch Parentsection (Adibou 3 only)\n");
        printf("10. Modify Adibou3.ini (Adibou 3 only)\n");
        printf("11. Run Uninstaller (UNINST.EXE)\n");
        printf("12. Start Le pays des Pierres magiques Intro\n");
        printf("13. Modify Adi5.ini (Adi 5 only)\n");
        printf("14. Open Licence Agreement\n");
        printf("15. Open MSG.DEF\n");
    } else if (Loader7Exists) {
        printf("Choose an option:\n");
        printf("1. Start loader7 with Debug Menu/Windowed mode\n");
        printf("2. Start loader7 in Fullscreen mode\n");
        printf("3. Modify mdo.ini\n");
        printf("4. Show Trace.txt (contains the output of Trace window from Debug Menu)\n");
        printf("5. Modify mdo.dbg\n");
        printf("6. Launch Parentsection (Adibou 3 only)\n");
        printf("7. Modify Adibou3.ini (Adibou 3 only)\n");
        printf("8. Run Uninstaller\n");
        printf("9. Start Le pays des Pierres magiques Intro\n");
        printf("10. Modify Adi5.ini (Adi 5 only)\n");
        printf("11. Open Licence Agreement\n");
        printf("12. Open MSG.DEF\n");
    } else if (Dev7VMExists) {
        printf("Choose an option:\n");
        printf("1. Start Dev7VM with Debug Menu/Windowed mode\n");
        printf("2. Start Dev7VM in Fullscreen mode\n");
        printf("3. Modify mdo.ini\n");
        printf("4. Show Trace.txt (contains the output of Trace window from Debug Menu)\n");
        printf("5. Modify mdo.dbg\n");
        printf("6. Launch Parentsection (Adibou 3 only)\n");
        printf("7. Modify Adibou3.ini (Adibou 3 only)\n");
        printf("8. Run Uninstaller (UNINST.EXE)\n");
        printf("9. Start Le pays des Pierres magiques Intro\n");
        printf("10. Modify Adi5.ini (Adi 5 only)\n");
        printf("11. Open Licence Agreement\n");
        printf("12. Open MSG.DEF\n");
    } else {
        printf("Error: Dev7VM.EXE or Loader7.exe is not found in the Game directory. Launcher terminated.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    std::cin >> choice;
    ConsoleUtils::printNewLine();

switch(choice) {
    case 1:
        if (Loader7Exists) {
            launchCommand("Loader7.exe -break");
            usedLoader7OrDev7VM = true;
        } else if (Dev7VMExists) {
            launchCommand("Dev7VM.exe -break");
            usedLoader7OrDev7VM = true;
        }
        break;
    case 2:
        if (Loader7Exists) {
            startGameExecutable();
            usedLoader7OrDev7VM = true;
        } else if (Dev7VMExists) {
            launchCommand("Dev7VM.exe");
            usedLoader7OrDev7VM = true;
        }
        break;
    case 3:
        modifyMDOIni();
        return 0;
    case 4:
        showTraceTXT();
        return 0;
    case 5:
        modifyMDODbg();
        return 0;
    case 6:
        if (Loader7Exists) {
            launchCommand("Loader7.exe -obc='B3_ParentLaunch'");
            usedLoader7OrDev7VM = true;
        } else if (Dev7VMExists) {
            launchCommand("Dev7VM.EXE -obc='B3_ParentLaunch'");
            usedLoader7OrDev7VM = true;
        }
        break;
    case 7:
        modifyAdibou3Ini();
        return 0;
    case 8:
        runUNINST();
        return 0;
    case 9:
        Ed4Intro();
        return 0;
    case 10:
        modifyAdi5Ini();
        return 0;
    case 11:
        openLicenceFile();
        return 0;
    case 12:
        showMSGDef();
        return 0;
    default:
        printf("Invalid choice. Launcher exits\n");
        TaskExecution::pressEnterToExit();
}

auto end = std::chrono::steady_clock::now(); // Record the end time
auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start); // Calculate elapsed time in seconds

// Convert seconds to hours, minutes, and seconds
int hours = elapsed.count() / 3600; // 3600 seconds in an hour
int minutes = (elapsed.count() % 3600) / 60; // Remaining minutes after extracting hours
int seconds = elapsed.count() % 60; // Remaining seconds after extracting minutes

if (usedLoader7OrDev7VM) {
    ConsoleUtils::clearConsole();
}

std::cout << "Total playtime: " << hours << " hours, " << minutes << " minutes and " << seconds << " seconds." << std::endl;

printf("Would you like to restart DEV7Launcher? (y/n): ");
char restartChoice;
std::cin >> restartChoice;

// y/Y english keyboard layout. j/J german kayboard layout. o/O french keyboard layout.
if (restartChoice == 'y' || restartChoice == 'Y' || restartChoice == 'j' || restartChoice == 'J' || restartChoice == 'o' | restartChoice == 'O') {
    printf("Delete temp files of DEV7Launcher...");
    #ifdef _WIN32
    int deleteMutexWin = system("del %temp%\\DEV7_INSTANCE_MUTEX");
    #else
    int deleteMutexUnix = system("rm /tmp/DEV7_INSTANCE_MUTEX");
    #endif
    ConsoleUtils::clearConsole(); // Clear the console before restarting
    main(argc, argv);  // Restart the launcher by calling main again
}

if (restartChoice == 'n' || restartChoice == 'N') {

    ConsoleUtils::clearConsole();
    return 1;

}

return 0;

} // End of namespace fs

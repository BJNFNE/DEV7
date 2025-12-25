#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

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
#define READ_WRITE_PERMISSION 0666
#endif

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
    char versionNumber[6] = "1.2.0";

    printf("=========================\n");
    printf(" DEV7Launcher ver. %s\n", versionNumber);
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
        system(SLEEP_COMMAND_UNIX) >= 0;
    #endif
}

int modifyMDOIni() {
    if (!fileExists("mdo.ini")) {
        fprintf(stderr, "Error: This directory does not seem to contain an configuration file in the directory.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    #ifdef _WIN32
        system("notepad mdo.ini") >= 0;
    #else
        execlp("nano", "nano", "mdo.ini", NULL);
        return 1;
    #endif
}

int showMSGDef() {
    if (!fileExists("msg.def")) {
        fprintf(stderr, "Error: This directory does not seem to contain an debug configuration file in the directory.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }
    #ifdef _WIN32
        system("notepad msg.def") >= 0;
    #else
        execlp("nano", "nano", "msg.def", NULL);
        return 1;
    #endif
}

int modifyMDODbg() {
    if (!fileExists("MDO.DBG")) {
        fprintf(stderr, "Error: MDO.DBG not found.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    #ifdef _WIN32
        system("notepad MDO.DBG") >= 0;
    #else
        execlp("nano", "nano", "MDO.DBG", NULL);
        return 1;
    #endif
}

int showTraceTXT() {
    if (!fileExists("Trace.txt")) {
        fprintf(stderr, "Error: This directory does not contain an Trace.txt.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    #ifdef _WIN32
        system("notepad Trace.txt") >= 0;
    #else
        execlp("nano", "nano", "Trace.txt", NULL);
        return 1;
    #endif
}

int modifyAdibou3Ini() {
    if (!fileExists("Adibou3.ini")) {
        fprintf(stderr, "Error: This directory does not seem to be an Adibou 3 game directory.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    // This an Workaround for this Function to load Adibou3.ini into the Editors
    // WORKAROUND: rename ADIBOU3.INI to Adibou3.ini so it will be read by the Editors as Adibou3.ini to avoid problems being loaded.
#ifdef _WIN32
  if (!fileExists("Adibou3.ini")) {
    system("ren ADIBOU3.INI Adibou3.ini") >= 0;
  }
    system("notepad Adibou3.ini") >= 0;
#else
  if (!fileExists("Adibou3.ini")) {
    system("mv ADIBOU3.INI Adibou3.ini") >= 0;
  }
   execlp("nano", "nano", "Adibou3.ini", NULL);
   return 1;
#endif
}

int modifyAdi5Ini() {
    if (!fileExists("Data/ADI5.ini")) {
        fprintf(stderr, "Error: This directory does not seem to be an Adi 5 game directory.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    #ifdef _WIN32
        system("notepad Data/ADI5.ini") >= 0;
    #else
        execlp("nano", "nano", "Data/ADI5.ini", NULL);
        return 1;
    #endif
}

void loadLicenceFile() {
    std::vector<std::string> txtFiles = {
        "Lizenzvereinbarung.txt", // German
        "garantie.txt",           // English
        "LISEZ MOI.txt",          // French
        "Техподдержка.txt"        // Russian
    };

    std::string filename;

    for (const auto& file : txtFiles) {
        if (fileExists(file)) {
            filename = file;
            break;
        }
    }

    if (!filename.empty()) {

#ifdef _WIN32
        int open = system(("notepad.exe " + filename).c_str());
#else
        int open = system(("open " + filename).c_str());
#endif

    } else {
        fprintf(stderr, "License file not found.\n");
    }
}

void runUNINST() {
    if (!fileExists("UNINST.EXE")) {
        fprintf(stderr ,"Error: UNINST.EXE not found in directory.\n");
        TaskExecution::pressEnterToExit();
        return;
    }
#ifdef _WIN32
    if (system("UNINST.EXE") != 0) {
    printf("Uninstaller has been started, Follow the Instructions to process the uninstallation.\n");
    }
#else
    if (system("wine UNINST.EXE") != 0) {
    printf("Uninstaller has been started over wine, Follow the Instructions to process the uninstallation.\n");
    }
#endif
}

void Ed4Intro() {
    if (!fileExists("Ed4Intro.exe")) {
        fprintf(stderr, "Error: This directory does not seem to be an Le Pays des pierres magiques game directory.\n");
        TaskExecution::pressEnterToExit();
        return;
    }
#ifdef _WIN32
    system("Ed4Intro.exe") >= 0;
#else
    execlp("wine", "wine", "Ed4Intro.exe", NULL);
#endif
}

void startGameExecutable() {
    struct ExecutableOption {
        std::string fileName;
        std::string command;
        bool useWine;
    };

    std::vector<ExecutableOption> executables = {
        {"LoaderMDO.exe", "LoaderMDO.exe", false},
        {"LoaderMDO.exe", "wine LoaderMDO.exe", true},
        {"Adibou3.EXE", "Adibou3.EXE", false},
        {"Adibou3.exe", "wine Adibou3.exe", true},
        {"adiboo3.exe", "adiboo3.exe", false},
        {"adiboo3.exe", "wine adiboo3.exe", true},
        {"ADI5.EXE", "ADI5.EXE", false},
        {"ADI5.exe", "wine ADI5.exe", true},
        {"Loader7.exe", "Loader7.exe", false},
        {"Loader7.exe", "wine Loader7.exe", true}
    };

    for (const auto& exe : executables) {
        if (fileExists(exe.fileName)) {
            printf("%s found. Starting %s...\n", exe.fileName, exe.command);
            launchCommand(exe.command);
            return;
        }
    }

    printf("None of the executables found.\nPlease make sure you have the exe in the same directory as the launcher.\n");
}


int main(int argc, char* argv[]) {
    auto start = std::chrono::steady_clock::now();
    
    int choice;
    bool usedLoader7OrDev7VM = false;

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
        fprintf(stderr, "Error: Dev7VM.EXE or Loader7.exe is not found in the Game directory. Launcher terminated.\n");
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
        loadLicenceFile();
        return 0;
    case 12:
        showMSGDef();
        return 0;
    default:
        fprintf(stderr, "Invalid choice. Launcher exits\n");
        TaskExecution::pressEnterToExit();
}

auto end = std::chrono::steady_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);

char hours = elapsed.count() / 3600;
char minutes = (elapsed.count() % 3600) / 60;
char seconds = elapsed.count() % 60;

if (usedLoader7OrDev7VM) {
    ConsoleUtils::clearConsole();
}

printf("Total playtime: %d hours, %d minutes, %d secounds.\n\n", hours, minutes, seconds);

printf("Would you like to restart DEV7Launcher? (y/n): ");
char restartChoice;
std::cin >> restartChoice;

// y/Y english keyboard layout. j/J german kayboard layout. o/O french keyboard layout.
if (restartChoice == 'y' || restartChoice == 'Y' || restartChoice == 'j' || restartChoice == 'J' || restartChoice == 'o' | restartChoice == 'O') {
    printf("Delete temp files of DEV7Launcher...");
    #ifdef _WIN32
    system("del %temp%\\DEV7_INSTANCE_MUTEX") >= 0;
    #else
    system("rm /tmp/DEV7_INSTANCE_MUTEX") >= 0;
    #endif
    ConsoleUtils::clearConsole();
    main(argc, argv);
}

if (restartChoice == 'n' || restartChoice == 'N') {

    ConsoleUtils::clearConsole();
    return 1;

}

return 0;

} // End of namespace fs
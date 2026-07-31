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
#include <shellapi.h>
#include <process.h>
#define SLEEP_COMMAND_WIN "ping -n 2 127.0.0.1 > nul"
#define DEV7_MUTEX_LAUNCH_WIN "%temp%/DEV7_INSTANCE_MUTEX"
#else
#include <unistd.h>
#include <sys/file.h>
#define SLEEP_COMMAND_UNIX "sleep 2"
#define DEV7_MUTEX_LAUNCH_UNIX "/tmp/DEV7_INSTANCE_MUTEX"
#define READ_WRITE_PERMISSION 0666
#endif

namespace fs = std::filesystem;

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

bool launchCommand(const std::string& cmd) {
    #ifdef _WIN32
        system(cmd.c_str());
    #else
        std::string wineCmd = "wine " + cmd;
        int result = system(wineCmd.c_str());
        system(SLEEP_COMMAND_UNIX) >= 0;
    #endif

    return 0x0ff; // Avoid compiler warning (gcc)
}

int modifyMDOIni() {
    if (!fs::exists("mdo.ini")) {
        fprintf(stderr, "Error: This directory does not seem to contain an configuration file in the directory.\n");
        TaskExecution::pressEnterToExit();
        return 0;
    }

    launchCommand("mdo.ini");
}

int showTraceTXT() {
    if (!fs::exists("Trace.txt")) {
        fprintf(stderr, "Error: This directory does not contain an Trace.txt.\n");
        TaskExecution::pressEnterToExit();
        return 0;
    }
        launchCommand("Trace.txt");
        return 1;
}

int modifyAdibou3Ini() {
    int smallIni = fs::exists("Adibou3.ini");
    int bigIni = fs::exists("ADIBOU3.INI");

    if (!bigIni && !smallIni) {
        fprintf(stderr, "Error: This directory does not seem to be an Adibou 3 game directory.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    if (bigIni) {
        std::error_code ec;
        fs::rename("ADIBOU3.INI", "Adibou3.ini", ec);
    }

    launchCommand("Adibou3.ini");
}

int modifyAdi5Ini() {
    if (!fs::exists("Data/ADI5.ini")) {
        fprintf(stderr, "Error: This directory does not seem to be an Adi 5 game directory.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }
        launchCommand("Data/ADI5.ini");
        return 1;
}

void Ed4Intro() {
    if (!fs::exists("Ed4Intro.exe")) {
        fprintf(stderr, "Error: This directory does not seem to be an Le Pays des pierres magiques game directory.\n");
        TaskExecution::pressEnterToExit();
        return;
    }

    launchCommand("Ed4Intro.exe");
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
        if (fs::exists(exe.fileName)) {
            std::cout << "%s found. Starting %s...\n" << exe.fileName << exe.command << std::endl;
            launchCommand(exe.command);
            return;
        }
    }

    printf("None of the executables found.\nPlease make sure you have the exe in the same directory as the Launcher.\n");
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::steady_clock::now();
    
    int choice;
    bool isGameExecutable = false;

    if (isDEV7Running()) {
        printf("A DEV7 client is already running, cannot handle more than one DEV7 client.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    // Start with searching first for "loader7.exe" which were offically shipped by Coktel Vision
    bool isDEV7Executable = (std::ifstream("loader7.exe").good() || std::ifstream("LOADER7.EXE").good()) || std::ifstream("Loader7.exe").good() || std::ifstream("Dev7VM.EXE").good();

    // execute here the printHeader() to display the Header (Program name with versionNumber)
    printHeader();

    if (isDEV7Executable) {
        printf("Choose an option:\n");
        printf("1. Start Game with Debug Menu/Windowed mode\n");
        printf("2. Start Game in Fullscreen mode\n");
        printf("3. Modify mdo.ini\n");
        printf("4. Show Trace.txt (contains the output of Trace window from Debug Menu)\n");
        printf("5. Launch Parentsection (Adibou 3 only)\n");
        printf("6. Modify Adibou3.ini (Adibou 3 only)\n");
        printf("7. Start Le pays des Pierres magiques Intro\n");
        printf("8. Modify Adi5.ini (Adi 5 only)\n");
    } else {
        fprintf(stderr, "Error: Dev7VM.EXE or Loader7.exe is not found in the Game directory. Launcher terminated.\n");
        TaskExecution::pressEnterToExit();
        return 1;
    }

    std::cin >> choice;
    ConsoleUtils::printNewLine();

switch(choice) {
    case 1:
        if (isDEV7Executable) {
            launchCommand("Loader7.exe -break");
            isGameExecutable = true;
        }
        break;
    case 2:
        if (isDEV7Executable) {
            startGameExecutable();
            isGameExecutable = true;
        }
        break;
    case 3:
        modifyMDOIni();
        return 0;
    case 4:
        showTraceTXT();
        return 0;
    case 5:
        if (isDEV7Executable) { // TODO: add check for Adibou3.ini to verify its Adibou3 and not any other Coktel game!
            launchCommand("Loader7.exe -obc='B3_ParentLaunch'");
            isGameExecutable = true;
        break;
    case 6:
        modifyAdibou3Ini();
        return 0;
    case 7:
        Ed4Intro();
        return 0;
    case 8:
        modifyAdi5Ini();
        return 0;
    default:
        fprintf(stderr, "Invalid choice. Launcher exits\n");
        TaskExecution::pressEnterToExit();
}

auto end = std::chrono::steady_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);

uint hours = elapsed.count() / 3600;
uint minutes = (elapsed.count() % 3600) / 60;
uint seconds = elapsed.count() % 60;

if (isGameExecutable) {
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
    char* tmpPath = getenv("TEMP");
    if (tmpPath != nullptr) {
        fs::path mutexPath = fs::path(tmpPath) / "DEV7_INSTANCE_MUTEX";
        fs::remove(mutexPath); 
    }
#else
    fs::remove("/tmp/DEV7_INSTANCE_MUTEX");
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
}
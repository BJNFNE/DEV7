#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#define SLEEP_COMMAND "ping -n 2 127.0.0.1 > nul"
#else
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>
#define SLEEP_COMMAND "sleep 2"
#endif

bool fileExists(const std::string& filename) {
#ifdef _WIN32
    return _access(filename.c_str(), 0) == 0;
#else
    struct stat buffer;
    return stat(filename.c_str(), &buffer) == 0;
#endif
}

void launchDEV7(const std::string& dev7Command, const std::string& loaderCommand) {
#ifdef _WIN32
    if (fileExists("Dev7VM.exe")) {
        system(dev7Command.c_str());
    } else if (fileExists("LOADER7.EXE") || fileExists("loader7.exe")) {
        system(loaderCommand.c_str());
    } else {
        std::cerr << "No suitable DEV7 client found. Dev7VM.exe, LOADER7.EXE, or loader7.exe is missing." << std::endl;
    }
    system(SLEEP_COMMAND);
#else
    // On Linux, we always try running the command with Wine
    std::string wineCommand = "wine " + dev7Command;
    if (fileExists("Dev7VM.exe")) {
        system(wineCommand.c_str());
        system(SLEEP_COMMAND);
    } else if (fileExists("LOADER7.EXE") || fileExists("loader7.exe")) {
        std::string wineLoaderCommand = "wine " + loaderCommand;
        system(wineLoaderCommand.c_str());
        system(SLEEP_COMMAND);
    } else {
        std::cerr << "No suitable DEV7 client found. Dev7VM.exe, loader7.exe is missing." << std::endl;
    }
#endif
}

int main(int argc, char* argv[]) {
    int choice;

    std::string dev7VMCommand = "Dev7VM.exe -break";
    std::string loaderCommand = "loader7.exe -break";

    std::cout << "Choose an option:\n";
    std::cout << "1. Start DEV7 with Debug Menu\n";
    std::cout << "2. Start DEV7 normal\n";
    std::cin >> choice;
    std::cout << "\n";

    if (choice == 1 || choice == 2) {
        launchDEV7(dev7VMCommand, loaderCommand);
    } else {
        std::cout << "Invalid choice. Please choose 1 or 2." << std::endl;
    }

    return 0;
}

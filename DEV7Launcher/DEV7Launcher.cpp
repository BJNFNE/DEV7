#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#define SLEEP_COMMAND "ping -n 2 127.0.0.1 > nul"
#define DEV7_MUTEX_NAME "DEV7_INSTANCE_MUTEX"
#else
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#define SLEEP_COMMAND "sleep 2"
#define DEV7_MUTEX_NAME "/tmp/DEV7_INSTANCE_MUTEX"
#endif

bool fileExists(const std::string& filename) {
#ifdef _WIN32
    return _access(filename.c_str(), 0) == 0;
#else
    struct stat buffer;
    return stat(filename.c_str(), &buffer) == 0;
#endif
}

bool isDev7Running() {
#ifdef _WIN32
    HANDLE mutex = CreateMutex(NULL, TRUE, DEV7_MUTEX_NAME);
    if (mutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(mutex);
        return true;
    }
#else
    int fd = open(DEV7_MUTEX_NAME, O_CREAT | O_RDWR, 0666);
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
    // On Linux, we always try running the command with Wine
    std::string wineCommand = "wine " + command;
    system(wineCommand.c_str());
#endif
    system(SLEEP_COMMAND);
}

void modifyMDOIni() {
#ifdef _WIN32
    system("notepad mdo.ini");
#else
    // On Linux, we always try running the command with Wine
    std::string modifyMDOIni = "nano mdo.ini";
    system(modifyMDOIni.c_str());
#endif

}

int main(int argc, char* argv[]) {
    int choice;

    if (isDev7Running()) {
        std::cout << "A DEV7 client is already running, cannot handle more than one DEV7 client." << std::endl;
        return 1;
    }

    bool loader7Exists = fileExists("loader7.exe");
    bool dev7VMExists = fileExists("Dev7VM.EXE");

    if (loader7Exists && dev7VMExists) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Start Dev7VM with Debug Menu\n";
        std::cout << "2. Start Dev7VM Normal\n";
        std::cout << "3. Start loader7 with Debug Menu\n";
        std::cout << "4. Start loader7 Normal\n";
        std::cout << "5. Modify mdo.ini\n";
    } else if (loader7Exists) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Start loader7 with Debug Menu\n";
        std::cout << "2. Start loader7 Normal\n";
        std::cout << "3. Modify mdo.ini\n";
    } else if (dev7VMExists) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Start Dev7VM with Debug Menu\n";
        std::cout << "2. Start Dev7VM Normal\n";
        std::cout << "3. Modify mdo.ini\n";
    } else {
        std::cout << "Error: Dev7VM.EXE or loader7.exe is not found in this Directory. Program halted." << std::endl;
        std::cout << "Press Enter to exit." << std::endl;
        getchar();
        return 1;
    }

    std::cin >> choice;
    std::cout << "\n";

    if (loader7Exists) {
        if (choice == 1) {
            launchCommand("loader7.exe -break");
        } else if (choice == 2) {
            launchCommand("loader7.exe");
        } else if (choice == 3) {
            modifyMDOIni(); // Call the function to modify mdo.ini
        } else {
            std::cout << "Invalid choice. Please choose a valid option." << std::endl;
        }
    } else if (dev7VMExists) {
        if (choice == 1) {
            launchCommand("Dev7VM.exe -break");
        } else if (choice == 2) {
            launchCommand("Dev7VM.exe");
        } else if (choice == 3) {
            modifyMDOIni(); // Call the function to modify mdo.ini
        } else {
            std::cout << "Invalid choice. Please choose a valid option." << std::endl;
        }
    }

    return 0;
}

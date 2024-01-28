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

bool isDev7Running() {
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

void modifyMDODbg() {
    std::string mdo_dbg = "MDO.DBG";

    if (!fileExists(mdo_dbg)) {
        std::cout << "Error: " << mdo_dbg << " not found in the directory." << std::endl;
        return;
    }

#ifdef _WIN32
    system("notepad MDO.DBG");
#else
    // On Linux, we always try running the command with Wine
    std::string modifyMDODbg = "nano MDO.DBG";
    system(modifyMDODbg.c_str());
#endif
}

void showTraceTXT() {
#ifdef _WIN32
    system("notepad Trace.txt");
#else
    // On Linux, we always try running the command with Wine
    std::string showTraceTXT = "nano --view Trace.txt";
    system(showTraceTXT.c_str());
#endif
}

void modifyAdibou3Ini() {
    // This an Workaround for this Function to load Adibou3.ini into the Editors
    // WORKAROUND: rename ADIBOU3.INI to Adibou3.ini so it will be read by the Editors as Adibou3.ini to avoid problems being loaded.
#ifdef _WIN32
  if (!std::filesystem::exists("Adibou3.ini")) {
    system("ren ADIBOU3.INI Adibou3.ini");
  }
  system("notepad Adibou3.ini");
#else
  if (!std::filesystem::exists("Adibou3.ini")) {
    system("mv ADIBOU3.INI Adibou3.ini");
  }
  system("nano Adibou3.ini");
#endif
}

void runUNINST() {
    std::string uninst = "UNINST.EXE";

    if (!fileExists(uninst)) {
        std::cout << "Error: " << uninst << " not found in directory." << std::endl;
        return;
    }
#ifdef _WIN32
    system("UNINST.EXE");
#else
    if (system("wine UNINST.EXE") != 0) {
    }
#endif
}

void Ed4Intro() {
    std::string Ed4IntroEXE = "Ed4Intro.exe";

    if (!fileExists(Ed4IntroEXE)) {
        std::cout << "Error: " << Ed4IntroEXE << " not found in directory." << std::endl;
        return;
    }
#ifdef _WIN32
    system("Ed4Intro.exe");
#else
    if (system("wine Ed4Intro.exe") != 0) {
    }
#endif
}

int main(int argc, char* argv[]) {
    int choice;

    if (isDev7Running()) {
        std::cout << "A DEV7 client is already running, cannot handle more than one DEV7 client." << std::endl;
        return 1;
    }

    bool loader7Exists = (std::ifstream("loader7.exe").good() || std::ifstream("LOADER7.EXE").good());
    bool dev7VMExists = fileExists("Dev7VM.EXE");

    if (loader7Exists && dev7VMExists) {
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
    } else if (loader7Exists) {
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
    } else if (dev7VMExists) {
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
    } else {
        std::cout << "Error: Dev7VM.EXE or loader7.exe is not found in the Game Directory. Launcher terminated." << std::endl;
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
        } else if (choice == 4) {
            showTraceTXT(); // Call the function to show Trace.txt
        } else if (choice == 5) {
            modifyMDODbg(); // Call the function to modify mdo.dbg
        } else if (choice == 6) {
            launchCommand("loader7.exe -obc='B3_ParentLaunch'");
        } else if (choice == 7) {
            modifyAdibou3Ini(); // Call the function to modify adibou3.ini
        } else if (choice == 8) {
            runUNINST(); // Call the function to run the Uninstaller 
        } else if (choice == 9) {
            Ed4Intro(); // Call the function to run the Intro of Le pays de Pierres Magiques
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
        } else if (choice == 4) {
            showTraceTXT(); // Call the function to show Trace.txt
        } else if (choice == 5) {
            modifyMDODbg(); // Call the function to modify mdo.dbg
        } else if (choice == 6) {
            launchCommand("Dev7VM.EXE -obc='B3_ParentLaunch'");
        } else if (choice == 7) {
            modifyAdibou3Ini(); // Call the function to modify adibou3.ini
        } else if (choice == 8) {
            runUNINST(); // Call the function to run the Uninstaller
        } else if (choice == 9) {
            Ed4Intro(); // Call the function to run the Intro of Le pays de Pierres Magiques 
        } else {
            std::cout << "Invalid choice. Please choose a valid option." << std::endl;
        }
    }
    return 0;
}
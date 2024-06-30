/*
LoaderMDO was used as Adibou3.EXE in Adibou 3 and as ADI5.EXE in ADI 5.
It was developed to be linked to Loader7.exe to run it.
***********************************************************************
This is an attempt to port that EXE in C++ to Linux.
It was originally developed for ADI 5 version 5.00 in the Year 2000.
Requirements:
-  Compile using g++ under Linux:
    g++ -o LoaderMDO LoaderMDO.cpp -pthread
*/ 

#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <cstring>

// Function prototype for starting Loader7.exe with arguments
void startLoader7(const char* arg);

int main() {
    // Check if a process with the name "LoaderMDO" is running
    // Sleep if LoaderMDO process exists
    if (access("LoaderMDO", F_OK) != -1) {
        usleep(100000); // Sleep for 100 milliseconds
    }

    // Create a named semaphore for process synchronization
    // Create semaphore named "/ADI5_LAUNCH_MUTEX" with initial value 1
    sem_t *mutex = sem_open("/ADI5_LAUNCH_MUTEX", O_CREAT | O_EXCL, 0644, 1);

    if (mutex != SEM_FAILED) {
        // Acquire the semaphore
        // Wait for the semaphore to become available
        sem_wait(mutex);

        // Launch Loader7.exe with Wine
        startLoader7("Loader7.exe");

      // Release the semaphore for other processes
        sem_post(mutex);

        // Close and unlink the semaphore
        sem_close(mutex);
        sem_unlink("/ADI5_LAUNCH_MUTEX");
    }

    return 0;
}

// Function definition for starting Loader7.exe with arguments
void startLoader7(const char* arg) {
    // Execute Loader7.exe using Wine
    execlp("wine", "wine", arg, nullptr);
}

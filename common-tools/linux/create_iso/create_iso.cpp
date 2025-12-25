/*
create_iso version 1.0

For create_iso its not required to use the original VolumeID for rebuilding the extracted ISO.

Requirements:
- Make sure to have genisoimage installed on your system to use create_iso properly.
*/

#include <iostream>
#include <string>

int main() {
    std::string directory, outputFileName;

    // Get directory path from the user
    printf("Enter the directory path to create ISO from: ");
    std::cin >> directory;

    // Get volume ID from the user
    std::string volumeId;
    printf("Enter the volume ID for the ISO image: ");
    std::cin >> volumeId;

    // Get output file name from the user
    printf("Enter the output file name for the ISO image (including file/directory path): ");
    std::cin >> outputFileName;

    // Create command to execute genisoimage
    std::string command = "genisoimage -o " + outputFileName + " -V '" + volumeId + "' -r -J -l " + directory;

    // Execute command
    int result = std::system(command.c_str());

    if (result == 0) {
        printf("ISO file created successfully.\n");
    } else {
        fprintf(stderr, "Error creating ISO file.\n");
    }

    return 0;
}
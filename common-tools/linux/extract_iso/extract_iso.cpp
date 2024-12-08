/*
extract_iso version 1.0
Compiling:
- To compile under gcc use this command: g++ -o extract_iso extract_iso.cpp -larchive

Requirements:
- Make sure to have under Linux libarchive-dev installed.
*/

#include <archive.h>
#include <archive_entry.h>
#include <iostream>
#include <fstream>
#include <cstring>

// Function to extract files from an ISO archive
bool extractISO(const char* isoPath, const char* destDir) {
    struct archive* a;
    struct archive* ext;
    struct archive_entry* entry;
    int flags;
    int r;

    // Set the flags to extract, handle symlinks, etc.
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM |
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    // Open the ISO file for reading
    a = archive_read_new();
    archive_read_support_format_iso9660(a); // Enable support for ISO9660 format
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, flags);
    archive_write_disk_set_standard_lookup(ext);

    if ((r = archive_read_open_filename(a, isoPath, 10240))) {
        std::cerr << "Error: Could not open ISO file: " << isoPath << std::endl;
        return false;
    }

    // Iterate through each file entry in the archive
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        std::string fullPath = std::string(destDir) + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, fullPath.c_str());

        // Extract the file
        r = archive_write_header(ext, entry);
        if (r < ARCHIVE_OK) {
            std::cerr << "Warning: " << archive_error_string(ext) << std::endl;
        } else {
            const void* buff;
            size_t size;
            la_int64_t offset;

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                r = archive_write_data_block(ext, buff, size, offset);
                if (r < ARCHIVE_OK) {
                    std::cerr << "Error writing data: " << archive_error_string(ext) << std::endl;
                    return false;
                }
            }

            if (r != ARCHIVE_EOF) {
                std::cerr << "Error reading data: " << archive_error_string(a) << std::endl;
                return false;
            }
        }

        r = archive_write_finish_entry(ext);
        if (r < ARCHIVE_OK) {
            std::cerr << "Error finishing entry: " << archive_error_string(ext) << std::endl;
            return false;
        }
    }

    // Clean up
    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    return true;
}

// Helper function to check if the file has the ".iso" extension
bool hasISOExtension(const std::string& filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".iso" || filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".ISO";
}

int main() {
    std::string isoPath, destDir;

    // Prompt the user for the ISO file path
    std::cout << "Enter the path to the ISO file (including .iso extension): ";
    std::getline(std::cin, isoPath);

    // Check if the file has a valid ".iso" extension
    if (!hasISOExtension(isoPath)) {
        std::cerr << "Error: The file must have a '.iso' extension." << std::endl;
        return 1;
    }

    // Prompt the user for the destination directory
    std::cout << "Enter the destination directory for extraction: ";
    std::getline(std::cin, destDir);

    // Extract the ISO
    if (extractISO(isoPath.c_str(), destDir.c_str())) {
        std::cout << "ISO extracted successfully to " << destDir << std::endl;
    } else {
        std::cerr << "Failed to extract ISO to " << destDir << std::endl;
    }

    return 0;
}

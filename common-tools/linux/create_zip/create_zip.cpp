#include <iostream>
#include <string>

using namespace std;

int main() {

// inputFolder for selecting which Folder should be used for the creation of the ZIP archive. 
std::string inputFolder;
printf("Navigate to the Path of the input Folder!");
std::cin >> inputFolder;

std::string outputZIP;
printf("Give me the Output directory for the ZIP archive");
std::cin >> outputZIP;

// Setup here the Program for creating ZIP archive from the Folder.

std::string zipCommand = "zip -r " + outputZIP + " " + inputFolder;

// Execute final Converter command.
int zipCmd = system(zipCommand.c_str());
return 0;
}

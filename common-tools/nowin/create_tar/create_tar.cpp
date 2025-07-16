#include <iostream>
#include <string>

using namespace std;

int main() {

// inputFolder for selecting which Folder should be used for the creation of the TAR archive. 
std::string inputFolder;
printf("Navigate to the Path of the input Folder!");
std::cin >> inputFolder;

std::string outputTAR;
printf("Give me the Output directory for the TAR archive");
std::cin >> outputTAR;

std::string tarCommand = "tar -cf \"" + outputTAR + "\" -C \"" + inputFolder + "\" .";

// Execute final TAR converter command.
int tarCmd = system(tarCommand.c_str());

return 0;

}

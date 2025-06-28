#include <iostream>
#include <string>

using namespace std;

int main() {

// inputISO for registering which ISO should be converted. 
std::string inputISO;
printf("Navigate to the Path of your ISO!");
std::cin >> inputISO;

std::string outputBIN;
printf("Give me the Output directory for the BIN file");
std::cin >> outputBIN;

// Setup here the Program for converting iso to bin

std::string converter = "dd if=" + inputISO + " of=" + outputBIN + " bs=2048 conv=sync,notrunc";

// Execute final Converter command.
int converterCmd = system(converter.c_str());

return 0;

}
// ConsoleUtils.h
#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <iostream>

namespace ConsoleUtils {
    inline void clearConsole() {
        std::cout << "\033[2J\033[H";
    }
}

#endif
// ConsoleUtils.h
#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <iostream>

namespace ConsoleUtils {
    inline void clearConsole() {
      puts("\033[2J\033[H");
    }
}
#endif
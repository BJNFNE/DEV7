#ifndef TASK_EXECUTION_H
#define TASK_EXECUTION_H

#include <iostream>

#include "common-code/ConsoleUtils.h"

namespace TaskExecution {
    inline void pressEnterToExit() {
      printf("Press Enter to exit");
      (void)getchar();
      ConsoleUtils::clearConsole();
    }

}
#endif
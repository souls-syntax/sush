#include <iostream>
#include "echo.h"

void cmd_exit(const std::vector<std::string> &strs) {
  throw ExitShell{};
}

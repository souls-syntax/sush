#include <iostream>
#include "builtins.h"


void cmd_exit(const std::vector<std::string> &strs) {
  throw ExitShell{};
}

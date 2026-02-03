#include <iostream>
#include <string>
#include "../../../utils/include/split.h"
#include "../../../commands/include/echo.h"
#include <vector>


void parseCommand(std::string& txt) {
  
  std::vector<std::string> v;
  int size = split(txt, v, ' ');
  
  if (v.empty()) {
    return;
  }

  std::string& command = v[0];

  if (command == "echo") {
    cmd_echo(v, 1);
  } else {
    std::cout << command << ": command not found" << "\n";
  }
}

#include <iostream>
#include <string>
#include "./internal/service/include/cmdParser.h"


int main() {

  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  
  for(;;) {
    std::cout << "$ ";
    std::string command;
    std::getline(std::cin, command);
    if (command == "exit") {
      break;
    } else if (command == "") {
      continue;
    }
    parseCommand(command);
  }
}

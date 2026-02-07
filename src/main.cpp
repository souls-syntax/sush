#include <iostream>
#include <string>
#include "cmdParser.h"
#include "builtins.h"

int main() {

  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  try {  
    for(;;) {
      std::cout << "$ ";
      std::string command;
      std::getline(std::cin, command);
      if(command == "") {
        continue;
      } 
      parseCommand(command);
    }
  } catch (const ExitShell&) {

  }

}

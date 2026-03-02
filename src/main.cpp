#include <iostream>
#include <string>
#include "cmdParser.h"
#include "builtins.h"
#include "recordHist.h"
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
      auto history = loadHistory();
      history.push_back(command);
      recordHist(command);
      parseCommand(command);
    }
  } catch (const ExitShell&) {
  }
}

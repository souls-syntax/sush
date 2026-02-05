#include <iostream>
#include <string>
#include "split.h"
#include "echo.h"
#include <vector>
#include "commandRegister.h"
#include "execStatus.h"

void parseCommand(std::string& txt) {
  
  std::vector<std::string> args;
  int size = split(txt, args, ' ');
  
  if (args.empty()) {
    return;
  }
  
  
  static const auto commands = getCommands();

  const std::string& name = args[0];

  auto it = commands.find(name);
  if(it != commands.end()) {
    it->second.callback(args);
    return;
  }

  if (executeExternal(args)) {
      return;
  }

  std::cout << name << ": command not found\n";

}

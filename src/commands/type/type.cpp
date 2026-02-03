#include <iostream>
#include <string>
#include <vector>
#include <commandRegister.h>

void cmd_type(const std::vector<std::string>& args) {
  static const auto commands = getCommands();

  const std::string& name = args[1];

  auto it = commands.find(name);
  if(it == commands.end()) {
    std::cout << name << ": not found\n";
    return;
  } else {
    std::cout << name << " is a shell builtin\n";
  }
}

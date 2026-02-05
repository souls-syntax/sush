#include <iostream>
#include <string>
#include <vector>
#include <commandRegister.h>
#include <execStatus.h>


void cmd_type(const std::vector<std::string>& args) {
  if (args.size() < 2) {
      std::cout << "type: missing operand\n";
      return;
  }
  static const auto commands = getCommands();

  const std::string& name = args[1];
  
  auto it = commands.find(name);
  if(it != commands.end()) {
    std::cout << name << " is a shell builtin\n";
    return;
  } 
  
  std::string namu = name; 
  std::string path = ExecStatus(namu);

  if (!path.empty()) {
      std::cout << name << " is " << path << "\n";
      return;
  }
  std::cout << name << ": not found\n";
}

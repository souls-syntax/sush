#pragma once

#include <string>
#include <vector>
#include <unordered_map>


struct cliCommand{
  std::string name;
  std::string description;
  void (*callback)(const std::vector<std::string>& args);
};

std::unordered_map<std::string, cliCommand> getCommands();

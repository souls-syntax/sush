#pragma once

#include <string>
#include <vector>

std::string GetPaths();
std::string ExecStatus(std::string &name);
bool isExecutable(std::string path);
bool executeExternal(const std::vector<std::string> &args);

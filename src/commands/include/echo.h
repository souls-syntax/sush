#pragma once
#include <vector>

struct ExitShell{};

void cmd_echo(const std::vector<std::string> &strs);
void cmd_type(const std::vector<std::string> &strs);
void cmd_exit(const std::vector<std::string> &strs);
void cmd_pwd(const std::vector<std::string> &strs);

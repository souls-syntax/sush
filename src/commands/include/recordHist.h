#pragma once

#include <string>
#include <vector>


void recordHist(const std::string& cmd);
std::string getHistPath();
std::vector<std::string> loadHistory();

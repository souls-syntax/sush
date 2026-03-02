#include <fstream>
#include <string>
#include "recordHist.h"

void recordHist(const std::string& cmd) {
  std::ofstream file(getHistPath(), std::ios::app);
  if(!file) {
    perror("sush: history open");
    return;
  }

  file << cmd << "\n";
}

std::string getHistPath() {
  const char* home = getenv("HOME");
  if(!home) return ".sushhist";
  return std::string(home) + "/.sushhist";
}


std::vector<std::string> loadHistory() {
  std::ifstream file(getHistPath());
  std::vector<std::string> history;
  std::string line;

  while(getline(file, line)) {
    history.push_back(line);
  }

  return history;
}

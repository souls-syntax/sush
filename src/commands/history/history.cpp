#include "recordHist.h"
#include <vector>
#include <string>
#include <iostream>

void cmd_hist(const std::vector<std::string> &strs) {
  std::vector<std::string> history = loadHistory();
  for(size_t i = 0; i < history.size(); i++) {
    std::cout << i+1 << " " << history[i] << "\n";
  }
}

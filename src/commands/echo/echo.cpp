#include <iostream>
#include <string>
#include <vector>

void cmd_echo(const std::vector<std::string> &strs) {
  for(int i = 1; i < strs.size(); i++) {
    std::cout << strs[i];
    if(i+1 < strs.size()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

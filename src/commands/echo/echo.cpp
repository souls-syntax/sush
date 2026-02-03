#include <iostream>
#include <string>
#include <vector>

void cmd_echo(std::vector<std::string> &strs, size_t size) {
  for(int i = size; i < strs.size(); i++) {
    std::cout << strs[i] << " ";
  }
  std::cout << "\n";
}

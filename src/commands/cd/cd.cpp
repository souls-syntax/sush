#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

void cmd_cd(const std::vector<std::string> &strs) {

  std::string s = strs[1];

  char* path; 
  if (s == "~") {
    path = getenv("HOME");
  } else {
    path = s.data();
  }

  int pk = chdir(path);
  if (pk != 0) {
    std::cout << "cd: "<< s <<": No such file or directory\n";
  }
}

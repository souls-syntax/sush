#include <unistd.h>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <vector>

void cmd_pwd(const std::vector<std::string> &strs){
  char buf[PATH_MAX];
  getcwd(buf, sizeof(buf));
  printf("%s\n",buf);
}

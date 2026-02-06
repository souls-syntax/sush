#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <iostream>

bool executeExternal(const std::vector<std::string> &args) {
  
  if (args.empty()) return false;

  std::vector<char*> argv;
  for(auto& s: args) {

    argv.push_back(const_cast<char*>(s.c_str()));
  }
  argv.push_back(NULL);
  
  pid_t pid = fork();

  if (pid == 0) {
    execvp(argv[0], argv.data());

    std::cout << argv[0] << ": command not found\n";
    _exit(1);

  }
  if (pid < 0) {
    return false;
  }

  int status;
  
  if (waitpid(pid, &status, 0) < 0) {
    return false;
  }

  return WIFEXITED(status);
}

#include <string>
#include "execStatus.h"
#include "split.h"
#include <vector>

std::string ExecStatus(std::string &name) {
  
  const char* env = std::getenv("PATH");
  
  std::string paths = env ? std::string(env) : "";
  
  std::vector<std::string> v;
  size_t vectorSize = split(paths,v,':');
  for (int i = 0; i < vectorSize; i++) {
    std::string envPath = v[i] + "/" + name;
    if(isExecutable(envPath)) {
      return envPath;
    }
  }
  return "";
}




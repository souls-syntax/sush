#include <cstdlib>
#include <string>


std::string GetPaths() {
  
  std::string path = std::getenv("PATH");
  return path;
} 

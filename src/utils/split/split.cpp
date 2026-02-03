#include <string>
#include <iostream>
#include <vector>

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch) {
  size_t pos = txt.find( ch );
  size_t initaiPos = 0;
  strs.clear();
  
  while( pos != std::string::npos) {
    strs.push_back(txt.substr(initaiPos, pos - initaiPos));
    initaiPos = pos+1;
    
    pos = txt.find(ch, initaiPos);
  }
  strs.push_back( txt.substr(initaiPos));
  
  return strs.size();
}

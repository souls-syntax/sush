#include <iostream>
#include <string>
#include "builtins.h"
#include <vector>
#include "commandRegister.h"
#include "execStatus.h"
#include "lexer.h"
#include "fsplit.h"
#include "expander.h"
#include "redirection.h"
  
void parseCommand(std::string& txt) {
  
  std::vector<Token> raw_segments;
  
  // size_t lexSegments(const std::string &txt, std::vector<Segment> &seg);
  // size_t expandSegments( std::vector<Segment> &segs );
  lexSegments(txt, raw_segments);
  expandSegments(raw_segments);

  std::vector<IOData> redirections;
  redirectionIdentifier(raw_segments,redirection);
  
  std::vector<std::string> args = fsplit(raw_segments);
  
  if (args.empty()) {
    return;
  }
  
  
  static const auto commands = getCommands();

  const std::string& name = args[0];

  auto it = commands.find(name);
  if(it != commands.end()) {
    it->second.callback(args);
    return;
  }

  if (executeExternal(args)) {
      return;
  }

  std::cout << name << ": command not found\n";
}

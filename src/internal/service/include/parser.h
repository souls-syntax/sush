#pragma once

#include "lexer.h"
#include <vector>

struct CommandNode {
  std::vector<std::string> args;
  std::vector<IOData> redirections;
};

std::vector<CommandNode> parser( std::vector<Token> &toks );

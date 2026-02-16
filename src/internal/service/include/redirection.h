#pragma once

#include "lexer.h"
//
// struct IOTrack {
//   std::string input_file;
//   std::string output_file;
//   std::string error_file;
//
//   bool redirect_input = false;
//   bool redirect_output = false;
//   bool append_output = false;
//   bool redirect_error = false;
// }

enum class RedirectType {
  Output,
  Append,
  Input,
  Heredoc
};

struct IOData {
  int fd;
  RedirectType rt;
  std::string target;
};

std::vector<IOData> redirections;

size_t redirectionIdentifier(std::vector<Token> &raw_segments,std::vector<IOData> &redirection);


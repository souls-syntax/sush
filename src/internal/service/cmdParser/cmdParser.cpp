#include <iostream>
#include <string>
#include <fcntl.h>
#include "builtins.h"
#include <vector>
#include "commandRegister.h"
#include "execStatus.h"
#include "lexer.h"
#include "fsplit.h"
#include "expander.h"
#include "redirection.h"
#include <unistd.h>
  
void parseCommand(std::string& txt) {
  
  std::vector<Token> raw_segments;
  
  // size_t lexSegments(const std::string &txt, std::vector<Segment> &seg);
  // size_t expandSegments( std::vector<Segment> &segs );
  lexSegments(txt, raw_segments);
  expandSegments(raw_segments);

  std::vector<IOData> redirections;
  redirectionIdentifier(raw_segments,redirections);
  
  std::vector<std::string> args = fsplit(raw_segments);
  
  if (args.empty()) {
    return;
  }
  
  
  static const auto commands = getCommands();

  const std::string& name = args[0];

  auto it = commands.find(name);
  
  int saved_stdout = dup(STDOUT_FILENO);
  int saved_stdin = dup(STDIN_FILENO);
  int saved_stderr = dup(STDERR_FILENO);

  bool redirectionStatus = false;

  for(auto& redir : redirections) {
      int fd = -1;
    if(redir.rt == RedirectType::Output) {
        fd = open(redir.target.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else if (redir.rt == RedirectType::Append) {
        fd = open(redir.target.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else if (redir.rt == RedirectType::Input) {
        fd = open(redir.target.c_str(), O_RDONLY);
    }

    if (fd < 0) {
        perror(("sush: " + redir.target).c_str());
        redirectionStatus = true;
        break;
    }

    dup2(fd,redir.fd);
    close(fd);
  }
  

    if (!redirectionStatus) {
          if(it != commands.end()) {
            it->second.callback(args);
          } else if (!executeExternal(args)) {
              std::cout << name << ": command not found\n";
          }
    }

    dup2(saved_stdout,STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stderr, STDERR_FILENO);
    close(saved_stdout);
    close(saved_stdin);
    close(saved_stderr);
    return;
}

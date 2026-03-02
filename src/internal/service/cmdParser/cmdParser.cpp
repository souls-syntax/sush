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
#include <sys/types.h>
#include "parser.h"
#include <sys/wait.h>

void parseCommand(std::string& txt) {
  
  std::vector<Token> raw_segments;
  
  // size_t lexSegments(const std::string &txt, std::vector<Segment> &seg);
  // size_t expandSegments( std::vector<Segment> &segs );
  lexSegments(txt, raw_segments);
  
  std::vector<CommandNode> pipeline = parser(raw_segments);

  if (pipeline.empty() || pipeline[0].args.empty()) {
    return;
  }
  
  if (pipeline.size() == 1) {

    std::vector<std::string>& args = pipeline[0].args;
    std::vector<IOData>& redirections = pipeline[0].redirections;
    
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

  
  
  int prevReadFd = -1;
  static const auto commands = getCommands();
   
  for(size_t i = 0; i < pipeline.size(); i++) {
  
    CommandNode& node = pipeline[i];
    bool isLast = (i == pipeline.size()-1);

    int pfds[2];


    if (!isLast) {
      if(pipe(pfds) == -1 ) {
        perror("sush: pipe error");
        return;
      }
    }

    pid_t pid = fork();
    if (pid == -1) {
      perror("sush: fork error");
      return;
    }

    if (pid == 0) {

      if(prevReadFd != -1) {
        dup2(prevReadFd, STDIN_FILENO);
        close(prevReadFd);
      }
      
      if (!isLast) {
        dup2(pfds[1], STDOUT_FILENO);
        close(pfds[0]);
        close(pfds[1]);
      }

      bool redirectionStatus = false;

      for(auto& redir : node.redirections) {
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

      if(redirectionStatus) {
        exit(1);
      }
      
      auto it = commands.find(node.args[0]);

      if(it != commands.end()) {
        it->second.callback(node.args);
        exit(0);
      } else if (!executeExternal(node.args)) {
        std::cout << node.args[0] << ": command not found\n";
        exit(127);
      }
      exit(0);
    } else {
      if(prevReadFd != -1) {
        close(prevReadFd);
      }

      if (!isLast) {
        close(pfds[1]);
        prevReadFd = pfds[0];
      }
    }
  }

  for (size_t i = 0; i < pipeline.size(); i++) {
    wait(NULL);
  }
}

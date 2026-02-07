#include <unordered_map>
#include "commandRegister.h"
#include "builtins.h"


std::unordered_map<std::string, cliCommand> getCommands() {
  return {
    {
      "echo", 
      {       
        "echo",
        "Repeat the args",
        cmd_echo
      }
    }, 
    { 
      "type",
      {      
        "type",
        "Show cmd type",
        cmd_type
      }
    },
    { 
      "exit",
      {      
        "exit",
        "exit the shell",
        cmd_exit
      }
    },
    { 
      "pwd",
      {      
        "pwd",
        "show current working directory",
        cmd_pwd
      }
    },
    { 
      "cd",
      {      
        "cd",
        "change current working directory",
        cmd_cd
      }
    }
  };
}

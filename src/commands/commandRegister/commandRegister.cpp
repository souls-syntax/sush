#include <unordered_map>
#include "commandRegister.h"
#include "echo.h"
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
    }
  };
}

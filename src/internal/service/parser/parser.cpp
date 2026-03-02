#include "lexer.h"
#include <vector>
#include <string>
#include "redirection.h"
#include "fsplit.h"
#include "expander.h"
#include "parser.h"

std::vector<CommandNode> parser( std::vector<Token> &toks ){
   std::vector<CommandNode> pipeline;
   std::vector<Token> tempTok;
   
   auto flushCommand = [&]() {
     if (tempTok.empty()) return;

     expandSegments(tempTok);

     CommandNode node;
     redirectionIdentifier(tempTok, node.redirections);

     node.args = fsplit(tempTok);

     pipeline.push_back(node);
     tempTok.clear();
   };

   for(auto& tok : toks) {
     if(tok.type == TokenType::Pipe) {
       flushCommand();
     } else {
       tempTok.push_back(tok);
     }
   }
   flushCommand();
   return pipeline;
}

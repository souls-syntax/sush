#include "split.h"
#include <vector>
#include <string>
#include "lexer.h"

std::vector<std::string> fsplit(std::vector<Token> &toks) {
    std::vector<std::string> finalString;
    for (auto& segs : toks){
        std::string finalToken;
        for (auto& seg : segs.parts) {
                finalToken += (seg.text);
        }
        finalString.push_back(finalToken);
    }
    return finalString;
}

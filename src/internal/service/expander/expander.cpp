#include "lexer.h"
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

size_t expandSegments(std::vector<Token> &toks) {
    for(auto& segs : toks) {
        for(auto& seg : segs.parts) {
            if (seg.quote == QuoteType::SingleQuote) {
                continue;
            }

            size_t pos = 0;
            while((pos = seg.text.find('$',pos)) != std::string::npos){
                if (pos + 1 >= seg.text.size()) {
                    break;
                }
                
                char next = seg.text[pos+1];
                if (next == ' ' || next == '\t' || next == '\0') {
                    pos++;
                    continue;
                }
                
                size_t end = pos + 1;
                while (end < seg.text.size() && (isalnum(seg.text[end]) || seg.text[end] == '_')) {
                    end++;
                }

                std::string varName = seg.text.substr(pos + 1, end - (pos + 1));
                const char* val = std::getenv(varName.c_str());
                std::string replacement = (val) ? val : "";
            
                seg.text.replace(pos,end-pos, replacement);
                pos += replacement.length();
                
            }
    
        }
    }
    return toks.size();
}





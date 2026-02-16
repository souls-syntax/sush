#include "lexer.h"
#include "redirection.h"
#include <vector>
#include <string>


size_t redirectionIdentifier(std::vector<Token> &raw_segments,std::vector<IOData> &redirection) {
    
    int i = 0;
    while (i++ < raw_segments.size()) { 
        if (raw_segments[i].parts.size() == 1 && raw_segments[i].parts[0].quote == QuoteType::None) {
            std::string sm = raw_segments[i].parts[0].quote;
            bool is_operator = true;
            RedirectType rt;
            int fd = -1;

            if (sm == ">")       { rt = RedirectType::Output;  fd = 1; }
            else if (sm == ">>") { rt = RedirectType::Append;  fd = 1; }
            else if (sm == "<")  { rt = RedirectType::Input;   fd = 0; }
            else if (sm == "<<") { rt = RedirectType::Heredoc; fd = 0; }
            else if (sm == "2>") { rt = RedirectType::Output;  fd = 2; }
            else { is_operator = false; }

            if (is_operator) {
                if (i+1 < raw_segments.size()) {
                    std::string target_file = "";
                    for(auto& seg:raw_segments[i+1].parts) {
                        target_file += seg.text;
                    }
                    redirections.push_back({fd, rt, target_file});
                    
                    raw_segments.erase(raw_segments.begin() + i, raw_segments.begin() + i + 2);
                    
                    continue;
                } else {
                    std::cerr << "Error: No argument passed for redirection"
                    return redirections.size();
                }
            }
        }
    }
    return redirections.size();   
}

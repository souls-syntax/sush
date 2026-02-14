#include <vector>
#include <string>
#include "lexer.h"

size_t lexSegments(const std::string &txt, std::vector<Token> &tok) {

   
    std::vector<Segment> seg;
    LexerState State = LexerState::Normal;
    std::string buf;
    
    // auto keyword means auto detect the type kinda like :=
    // [&] let you get all the outside by refrence [=] for copy, [] for no ref, [&buf] for specific ref

    // Lambda functions for cleanup
    auto flush = [&](QuoteType q) {
        if(!buf.empty()) {
            seg.push_back({buf,q});
            buf.clear();
        }
    };
    auto flushToken = [&]() {
        if (!seg.empty()) {
            tok.push_back(Token{seg});
            seg.clear();
        }      
    };

    for (size_t i = 0; i < txt.size(); i++) {

        char c = txt[i];
        switch(State) {

            case LexerState::Normal:
                    
                if (c == '\'') {
                    flush(QuoteType::None);
                    State = LexerState::IsSingleQuote;
                }
                else if (c == '"') {
                    flush(QuoteType::None);
                    State = LexerState::IsDoubleQuote;
                }
                
                else if (std::isspace(static_cast<unsigned char>(c))) {
                    flush(QuoteType::None);
                    flushToken();
                }
                else {buf += c;}
                break;
        case LexerState::IsSingleQuote:
            if (c == '\'') {
                    flush(QuoteType::SingleQuote);
                    State = LexerState::Normal;
                } else {
                    buf += c;
                }
            break;
        case LexerState::IsDoubleQuote:
            if (c == '"') {
                    flush(QuoteType::DoubleQuote);
                    State = LexerState::Normal;
            } else {
                    buf += c;
                }
            break;
        }
    }
    if (State == LexerState::Normal) {
        flush(QuoteType::None);
    } else if (State == LexerState::IsDoubleQuote) {
        flush(QuoteType::DoubleQuote);
    } else {
        flush(QuoteType::SingleQuote);
    }
    flushToken();

    return tok.size();
}

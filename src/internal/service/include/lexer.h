#pragma once
#include <string>
#include <vector>

enum class TokenType {
  Word,
  Pipe,
  Redirect,
 };


enum class QuoteType {
  None,
  SingleQuote,
  DoubleQuote
};

enum class LexerState {
  Normal,
  IsSingleQuote,
  IsDoubleQuote
};


struct Segment {
    std::string text;
    QuoteType quote;
};

struct Token {
  TokenType type;
  std::vector<Segment> parts;
};

size_t lexSegments(const std::string &txt, std::vector<Token> &tok);

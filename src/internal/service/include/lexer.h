#pragma once
#include <string>
#include <vector>

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
  std::vector<Segment> parts;
};
size_t lexSegments(const std::string &txt, std::vector<Token> &tok);

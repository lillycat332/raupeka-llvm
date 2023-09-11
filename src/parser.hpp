#pragma once
#include <string>

namespace Raupeka::Syntax::Lexer {
  struct Token {
    enum class Type {
      Identifier,
      Number,
      String,
      Operator,
      Keyword,
      Punctuation,
      Whitespace,
      Comment,
      Eof,
      Let,
      Import
    };
    Type type;
    std::string value;
  };

  class Lexer {
  public:
    Lexer() : input(""), current(input.begin()), end(input.end()) {}
    Token next_token();

  private:
    std::string input;
    std::string::iterator current;
    std::string::iterator end;
  };
} // namespace Raupeka::Syntax::Lexer

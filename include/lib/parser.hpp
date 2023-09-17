#pragma once
#include <string>
#include <typeinfo>
#include <vector>

namespace Raupeka::Syntax::Lexer {
  struct Token {
    enum class Type {
      Identifier,
      Number,
      String,
      Operator,
      Punctuation,
      Whitespace,
      Comment,
      Eof,
      // Keywords
      Let,
      Import,
      Foreign,
      CCall,
      As,
      Module,
      Begin,
      End,
      Perform,
      Effect,
      Type,
      Data,
      TypeFamily,
      Trait,
      Instance,
      Match,
      With,
      Forall,
      Underscore,
      Resume,
      If,
      Then,
      Else,
      ScopeResolution,
      Assignment,
      Unknown,
      LParen,
      RParen,
      LBrace,
      RBrace,
      LSquare,
      RSquare,
      Bang,
      Comma,
      Colon,
      LArrowBind,
      RArrowTy,
      WhitespaceIndent,
      WhitespaceNewline
    };
    Type type;
    std::string value;
    /**
     * @brief Return a string representation of the token.
     * @note This representation does not display a human-readable token type,
     * as it is implemented using an enum.
     * @return std::string - A string representation of the token.
     */
    std::string str();
  };
  inline std::ostream &operator<<(std::ostream &os, Token &token) {
    return os << token.str();
  }

  /**
   * @brief The Lexer class is responsible for tokenizing a string.
   * @note This class is not responsible for parsing the tokens into an AST.
   * That is the job of the Parser class.
   */
  class Lexer {
  public:
    /**
     * @brief Construct a new Lexer object
     *
     * @param s The string to tokenize.
     */
    Lexer(std::string s) : input(s), current(input.begin()), end(input.end()) {}
    /**
     * @brief Return the next token in the input string.
     *
     * @return Token
     */
    Token next_token();

    /**
     * @brief Return the current token in the input string.
     *
     * @note This function does not advance the iterator and thus is pure.
     * @return Token
     */
    Token peek_token() const { return current_token; }
    /**
     * @brief Tokenize the full input string, returning a vector of tokens.
     *
     * @return std::vector<Token>
     */
    std::vector<Token> tokenize();

    void skip_whitespace();
    void skip_comment();
    void skip_line_comment();
    void skip_block_comment();

  private:
    std::string input;
    Token current_token;
    std::string::iterator current;
    std::string::iterator end;
  };
} // namespace Raupeka::Syntax::Lexer

namespace Raupeka::Syntax::Parser {
  class Parser {
  public:
    Parser(std::vector<Lexer::Token> tokens)
        : tokens(tokens), current(tokens.begin()), end(tokens.end()) {}
    Lexer::Token next_token();
    Lexer::Token peek_token() const { return *current; }
    std::vector<Lexer::Token> tokens;
    std::vector<Lexer::Token>::iterator current;
    std::vector<Lexer::Token>::iterator end;
  };
} // namespace Raupeka::Syntax::Parser

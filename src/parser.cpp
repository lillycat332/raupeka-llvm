#include "../include/lib/parser.hpp"
#include "../include/lib/ast.hpp"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <variant>
#include <vector>
#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

namespace Raupeka::Syntax::Lexer {
  Token Lexer::next_token() {
    if (current == end) {
      this->current_token = {Token::Type::Eof, "EOF"};
    }

    auto indent_token = [this]() {
      std::string value;
      while (*current == ' ') {
        value += *current;
        current++;
      }
      if (value != " " && value != "") {
        this->current_token = {Token::Type::Whitespace, value};
        return true;
      }
      return false;
    };

    if (indent_token()) {
      return this->current_token;
    }

    while (current != end && *current == '\n') {
      this->current_token = {Token::Type::WhitespaceNewline, ""};
      current++;
      return this->current_token;
    }

    // skip comments
    if (*current == '-') {
      current++;
      if (*current == '-') {
        std::string value;
        current++;
        while (*current != '\n') {
          value += *current;
          current++;
        }
        this->current_token = {Token::Type::Comment, value};
      }
    }

    if (std::isalpha(*current)) {
      std::string value;
      while (std::isalnum(*current)) {
        value += *current;
        current++;
      }
      // match on value
      if (value == "let") {
        this->current_token = {Token::Type::Let, value};
      } else if (value == "import") {
        this->current_token = {Token::Type::Import, value};
      } else if (value == "if") {
        this->current_token = {Token::Type::If, value};
      } else if (value == "else") {
        this->current_token = {Token::Type::Else, value};
      } else if (value == "then") {
        this->current_token = {Token::Type::Then, value};
      } else if (value == "begin") {
        this->current_token = {Token::Type::Begin, value};
      } else if (value == "end") {
        this->current_token = {Token::Type::End, value};
      } else if (value == "forall") {
        this->current_token = {Token::Type::Forall, value};
      } else if (value == "as") {
        this->current_token = {Token::Type::As, value};
      } else if (value == "module") {
        this->current_token = {Token::Type::Module, value};
      } else if (value == "perform") {
        this->current_token = {Token::Type::Perform, value};
      } else if (value == "effect") {
        this->current_token = {Token::Type::Effect, value};
      } else if (value == "type") {
        this->current_token = {Token::Type::Type, value};
      } else if (value == "data") {
        this->current_token = {Token::Type::Data, value};
      } else if (value == "typefamily") {
        this->current_token = {Token::Type::TypeFamily, value};
      } else if (value == "trait") {
        this->current_token = {Token::Type::Trait, value};
      } else if (value == "instance") {
        this->current_token = {Token::Type::Instance, value};
      } else if (value == "match") {
        this->current_token = {Token::Type::Match, value};
      } else if (value == "with") {
        this->current_token = {Token::Type::With, value};
      } else if (value == "resume") {
        this->current_token = {Token::Type::Resume, value};
      } else if (value == "foreign") {
        this->current_token = {Token::Type::Foreign, value};
      } else if (value == "ccall") {
        this->current_token = {Token::Type::CCall, value};
      } else {
        this->current_token = {Token::Type::Identifier, value};
      }

      return this->current_token;
    } // handle numbers
    else if (std::isdigit(*current)) {
      std::string value;
      while (std::isdigit(*current)) {
        value += *current;
        current++;
      }
      this->current_token = {Token::Type::Number, value};
      current++;
      return this->current_token;
    } // handle strings
    else if (*current == '"') {
      std::string value;
      current++;
      while (*current != '"') {
        value += *current;
        current++;
      }

      this->current_token = {Token::Type::String, value};
      // std::cout << this->current_token << std::endl;
      current++;
      return this->current_token;
    } // handle EOF
    else if (current == end) {
      this->current_token = {Token::Type::Eof, "EOF"};
      // std::cout << this->current_token << std::endl;
      current++;
      return this->current_token;
    } // handle brackets
    else if (*current == '(') {
      this->current_token = {Token::Type::LParen, "("};
      current++;
      return this->current_token;
    } else if (*current == ')') {
      this->current_token = {Token::Type::RParen, ")"};
      current++;
      return this->current_token;
    } else if (*current == '{') {
      this->current_token = {Token::Type::LBrace, "{"};
      current++;
      return this->current_token;
    } else if (*current == '}') {
      this->current_token = {Token::Type::RBrace, "}"};
      current++;
      return this->current_token;
    } // handle operators
    else if (std::ispunct(*current)) {
      std::string value;
      // while
      while (std::ispunct(*current) && *current != '(' && *current != ')' &&
             *current != '"' && *current != '{' && *current != '}') {
        value += *current;
        current++;
      }
      // match on value
      if (value == "::") {
        this->current_token = {Token::Type::ScopeResolution, value};
      } else if (value == "=") {
        this->current_token = {Token::Type::Assignment, value};
      } else if (value == "->") {
        this->current_token = {Token::Type::RArrowTy, value};
      } else if (value == "<-") {
        this->current_token = {Token::Type::LArrowBind, value};
      } else if (value == "!") {
        this->current_token = {Token::Type::Bang, value};
      } else if (value == ",") {
        this->current_token = {Token::Type::Comma, value};
      } else if (value == ":") {
        this->current_token = {Token::Type::Colon, value};
      } else if (value == "{") {
        this->current_token = {Token::Type::LBrace, value};
      } else if (value == "}") {
        this->current_token = {Token::Type::RBrace, value};
      } else {
        std::cout << "operator: " << value << std::endl;
        this->current_token = {Token::Type::Operator, value};
      }
      return this->current_token;
    } // handle unknown
    else {
      std::string value;
      value += *current;
      current++;
      this->current_token = {Token::Type::Unknown, value};
      return this->current_token;
    }
  }

  std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token;
    do {
      token = this->next_token();
      tokens.push_back(token);
    } while (token.type != Token::Type::Eof);
    return tokens;
  }

  void Lexer::skip_line_comment() {
    if (*current == '/') {
      current++;
      if (*current == '/') {
        current++;
        while (*current != '\n') {
          current++;
        }
      }
    }
  }

  void Lexer::skip_block_comment() {
    if (*current == '/') {
      current++;
      if (*current == '*') {
        current++;
        while (*current != '*' && *(current + 1) != '/') {
          current++;
        }
      }
    }
  }

  void Lexer::skip_comment() {
    skip_line_comment();
    skip_block_comment();
  }

  std::string Token::str() {
    return std::string("Token(") + std::to_string(static_cast<int>(type)) +
           ", " + value + ")";
  }
} // namespace Raupeka::Syntax::Lexer

namespace Raupeka::Syntax::Parser {
  using namespace Tree;
  using namespace Lexer;

} // namespace Raupeka::Syntax::Parser

#include "parser.hpp"
#include "ast.hpp"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
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
#include <string>
#include <tuple>
#include <variant>
#include <vector>

namespace Raupeka::Syntax::Lexer {
  Token Lexer::next_token() {
    if (current == end) {
      return {Token::Type::Eof, ""};
    }

    if (std::isalpha(*current)) {
      std::string value;
      while (std::isalnum(*current)) {
        value += *current;
        current++;
      }
      if (value == "let") {
        return {Token::Type::Let, value};
      } else if (value == "import") {
        return {Token::Type::Import, value};
      } else {
        return {Token::Type::Identifier, value};
      }
    }
    return {Token::Type::Eof, ""};
  }
} // namespace Raupeka::Syntax::Lexer

namespace Raupeka::Syntax::Parser {
  using namespace Tree;

} // namespace Raupeka::Syntax::Parser

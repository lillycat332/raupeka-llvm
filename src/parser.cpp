#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <variant>
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
#include <vector>

namespace Raupeka::Syntax::Tree {

  struct Application;
  struct LetBinding;
  struct TySig;
  struct IfExpr;
  struct MatchExpr;
  struct LambdaExpr;
  struct BinopExpr;

  using Expr = std::variant<Application, LetBinding, TySig, IfExpr, MatchExpr,
                            LambdaExpr, BinopExpr>;

  struct Application {
    std::string name;
    std::vector<std::string> args;
  };

  struct LetBinding {
    std::string name;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Expr> body;
  };

  struct TySig {
    std::string name;
    std::string ty;
  };

  struct IfExpr {
    std::unique_ptr<Expr> cond;
    std::unique_ptr<Expr> then;
    std::unique_ptr<Expr> else_;
  };

  struct MatchExpr {
    std::unique_ptr<Expr> expr;
    std::vector<std::tuple<std::string, std::vector<std::string>,
                           std::unique_ptr<Expr>>>
        cases;
  };

  struct LambdaExpr {
    std::vector<std::string> args;
    std::unique_ptr<Expr> body;
  };

  struct BinopExpr {
    std::string op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
  };

} // namespace Raupeka::Syntax::Tree

namespace Raupeka::Compiler {
  using namespace Raupeka::Syntax::Tree;
  struct CompilerContext {
    static std::unique_ptr<llvm::LLVMContext> context;
    static std::unique_ptr<llvm::IRBuilder<>> builder;
    static std::unique_ptr<llvm::Module> module;
    static std::map<std::string, llvm::Value *> named_values;
  };

} // namespace Raupeka::Compiler

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
    Lexer(std::string input) {
      this->input = input;
      current = this->input.begin();
      end = this->input.end();
    }

    Token next_token() {
      if (current == end) {
        return {Token::Type::Eof, ""};
      };

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

  private:
    std::string input;
    std::string::iterator current;
    std::string::iterator end;
  };
} // namespace Raupeka::Syntax::Lexer

namespace Raupeka::Syntax::Parser {
  using namespace Tree;

} // namespace Raupeka::Syntax::Parser

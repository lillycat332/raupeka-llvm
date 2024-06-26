#pragma once
#include <string>
#include <variant>
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

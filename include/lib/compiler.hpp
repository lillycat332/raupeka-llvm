#pragma once
#include "ast.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Raupeka::Compiler {
  using namespace Raupeka::Syntax::Tree;
  struct CompilerContext {
    static std::unique_ptr<llvm::LLVMContext> context;
    static std::unique_ptr<llvm::IRBuilder<>> builder;
    static std::unique_ptr<llvm::Module> module;
    static std::map<std::string, llvm::Value *> named_values;
  };
} // namespace Raupeka::Compiler

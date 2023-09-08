#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  // Open a new context and module.
  std::unique_ptr<llvm::LLVMContext> Context =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::Module> Module =
      std::make_unique<llvm::Module>("JITContext", *Context);

  // Create a new builder for the module.
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*Context);
  return 0;
}
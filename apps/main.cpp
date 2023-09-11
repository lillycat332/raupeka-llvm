#include <algorithm>
#include <boost/program_options.hpp>
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

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  for (char *arg : std::vector<char *>(argv, argv + argc)) {
    std::cout << arg << std::endl;
  }

  // Parse command line options.
  po::options_description desc("Allowed options");

  // formatter makes this look ugly.
  // clang-format off
  desc.add_options()
    ("help", "produce help message")
    ("input-file", po::value<std::string>(), "input file")
    ("output-file", po::value<std::string>(), "output file")
    ("optimization", po::value<int>())
    ("verbose", "verbose output");
  // clang-format on

  po::variables_map vm;

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

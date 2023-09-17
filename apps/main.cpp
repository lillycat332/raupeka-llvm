#include "../include/lib/parser.hpp"
#include <fstream>
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  for (char *arg : std::vector<char *>(argv, argv + argc)) {
    std::cout << arg << std::endl;
  }

  // Parse command line options.
  // po::options_description desc("Allowed options");

  // formatter makes this look ugly.
  // clang-format off
  // desc.add_options()
  //   ("help", "produce help message")
  //   ("input-file", po::value<std::string>(), "input file")
  //   ("output-file", po::value<std::string>(), "output file")
  //   ("optimization", po::value<int>())
  //   ("verbose", "verbose output");
  // clang-format on

  // po::variables_map vm;

  // Open a new context and module.
  std::unique_ptr<llvm::LLVMContext> Context =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::Module> Module =
      std::make_unique<llvm::Module>("JITContext", *Context);

  // Create a new builder for the module.
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*Context);

  // read input file
  if (argc > 1) {
    std::cout << "input file: " << argv[1] << std::endl;
  } else {
    std::cout << "no input file specified" << std::endl;
    return 0;
  }

  std::string input_file = argv[1];
  std::string output_file = "a.out";
  std::fstream file(input_file);
  std::stringstream data;
  data << file.rdbuf();

  const std::string example_string = "let x = 1";
  Raupeka::Syntax::Lexer::Lexer lexer(data.str());
  auto tokens = lexer.tokenize();
  for (Raupeka::Syntax::Lexer::Token token : tokens) {
    std::cout << token << std::endl;
  }

  return 0;
}

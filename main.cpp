#include <cstdio>
#include <iostream>
#include <string>

#include "Interpreter/Interpreter.h"
#include "Parser/Absyn.H"
#include "Parser/ParserError.H"
#include "Parser/ParserWrapper.h"
#include "Parser/Printer.H"

int main(int argc, char** argv) {
  FILE* file = nullptr;
  Program* parse_tree = NULL;
  Interpreter* interpreter = new Interpreter();
  if (argc > 1) {
    if (strcmp(argv[1], "-h") == 0) {
      // Print the usage
      std::cout
          << "usage: Call with one of the following argument combinations:\n"
          << "\t<file-name>\t\tAny input file with pre written functions and "
             "operators.\n"
          << "\t-h\t\tDisplay this help message.\n";
      return 0;
    } else { // If there is a file name given then parse and interpret that
      file = fopen(argv[1], "r");
      if (!file) {
        std::cerr << "Could not open file " << argv[1] << "\n";
        return 1;
      }
    }
  }

  // Print a one line information
  std::cout << "====================================\n"
            << "===========> Flomathica <===========\n"
            << "====================================\n"
            << "-------Predefined functions---------\n"
            << "  exit()         to exit\n"
               "  _toggle_ir()   to toggle LLVM IR\n"
               "  _broom()       to clear the screen\n"
               "  ? \"\"           to view the help\n"
            << "------------------------------------\n";

  // If there is a preloaded file load that in first
  if (file != nullptr) {
    std::string error_msg;
    parse_tree = ParseTree(file, error_msg);
    if (!error_msg.empty()) { // Parse error if error_msg not empty
      std::cerr << "Error parsing " << argv[1] << ": " << error_msg;
      return 1;
    }
    interpreter->interpret(parse_tree, false);
  }

  std::string input;
  std::string command;
  bool print_llvm_ir = false;
  while (1) {
    std::cout << (command.empty() ? ">>> " : "... ");
    std::getline(std::cin >> std::noskipws, input);
    command += (command.empty() ? "" : "\n") + input;

    // First a few builtins
    if (input == "exit()" || input == "#") {
      return 0;
    } else if (input == "_toggle_ir()") {
      print_llvm_ir = !print_llvm_ir;
      command = "";
      continue;
    } else if (input == "_broom()") {
#ifdef __unix__
      system("clear");
#else
      system("cls");
#endif
      command = "";
      continue;
    } else if (input.empty()) {
      continue;
    } else if ((command.size() > 2 && command[0] == 'd' && command[1] == 'e' &&
                command[2] == 'f') || // If starts with def get next line
               (command.size() > 7 && command[0] == 'o' && command[1] == 'p' &&
                command[2] == 'e' && command[3] == 'r' && command[4] == 'a' &&
                command[5] == 't' && command[6] == 'o' &&
                command[7] == 'r')) { // Or if starts with operator
      if (input.find('!') == -1) {    // Only skip if there is no '!'
        continue;
      }
    }

    std::string error_msg;
    parse_tree = ParseTree(command, error_msg);
    if (!error_msg.empty()) { // Parse error if error_msg not empty
      std::cerr << error_msg;
      command = ""; // Reset the command if there was a syntax error
      continue;
    }

    if (parse_tree) {
      // Interpret the parse tree
      interpreter->interpret(parse_tree, print_llvm_ir);

      command = ""; // Reset the command after it ran trough
    }
  }
  return 1;
}

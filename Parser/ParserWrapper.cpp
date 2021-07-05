#include "ParserWrapper.h"
#include "ParserError.H"

Program* ParseTree(const std::string& input, std::string& error_msg) {
  Program* parse_tree = nullptr;
  try {
    parse_tree = pProgram(input.c_str());
  } catch (parse_error& e) {
    error_msg = "Parse error on line " + std::to_string(e.getLine());
    error_msg += "\n";
  }
  return parse_tree;
}

Program* ParseTree(FILE* file, std::string& error_msg) {
  Program* parse_tree = nullptr;
  try {
    parse_tree = pProgram(file);
  } catch (parse_error& e) {
    error_msg = "Parse error on line " + std::to_string(e.getLine());
    error_msg += "\n";
  }
  return parse_tree;
}
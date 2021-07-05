#ifndef PARSERWRAPPER_HEADER
#define PARSERWRAPPER_HEADER
#include "Parser.H"

Program* ParseTree(FILE* file, std::string& error_msg);

Program* ParseTree(const std::string& input, std::string& error_msg);

#endif
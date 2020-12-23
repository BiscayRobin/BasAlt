#pragma once

#include <fstream>
#include <vector>

#include "token.hpp"

class Lexer {
    char curChar = EOF;
    std::ifstream &file;

   public:
    Lexer(std::ifstream &file);
    std::vector<Token> lex();

   private:
    bool next();
    Token makeNumber();
    double readDecimal();
    Token makeVarOrKeyword();
    Token makeString();
};

#pragma once

#include <fstream>
#include <vector>

#include "token.hpp"

std::vector<Token> lex(std::ifstream &file);

Token makeNumber(std::ifstream &file, char c);

double readDecimal(std::ifstream &file, char c);

Token makeVarOrKeyword(std::ifstream &file, char c);

Token makeString(std::ifstream &file, char starter);

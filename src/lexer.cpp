#include "lexer.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "token.hpp"

Lexer::Lexer(std::ifstream& f) : file(f) {}

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens = {};
    next();
    while (file.good()) {
        switch (curChar) {
            case '(': {
                next();
                if(curChar == '*')
                    ignoreComments();
                else
                    tokens.push_back(Token{Token::TkType::l_paren});
                break;
            }
            case ')': {
                tokens.push_back(Token{Token::TkType::r_paren});
                next();
                break;
            }
            case '\n': {
                tokens.push_back(Token{Token::TkType::line_sep}); 
                next(); 
                break;
            }
            case '0' ... '9': tokens.push_back(makeNumber()); break;
            case 'a' ... 'z':
            case 'A' ... 'Z': tokens.push_back(makeVarOrKeyword()); break;
            case '\'':
            case '"': tokens.push_back(makeString()); next(); break;
            case '+': tokens.push_back(Token{Token::TkType::plus}); next(); break;
            case ':': tokens.push_back(Token{Token::TkType::colon}); next(); break;
            default: 
                if(isblank(curChar))
                    next();
                else {
                    //should switch to an error later in development
                    std::cout << "couldn't parse: " << static_cast<int>(curChar) << "\n";
                    next();
                }
            break;
        }
    }
    return tokens;
}

bool Lexer::next() { return file.get(curChar).good(); }

Token Lexer::makeNumber() {
    double num = 0.;
    if (curChar == '0') {  // special cases (binary hexadecimal octal ...)
        next();
        switch (toupper(curChar)) {
            case '0' ... '9':
                // num = readOctal(file, c);
                break;
            case 'B':
                // num = readBinary(file);
                break;
            case 'X':
                // num = readHexadecimal(file);
                break;
            default:
                // should be an error
                break;
        }
    } else if (curChar >= '1' && curChar <= '9') {
        num = readDecimal();
    } else {
        // should be an error
    }

    return Token{Token::TkType::number_lit, num};
}

double Lexer::readDecimal() {
    double num = curChar - '0';
    bool exit = false;
    bool decimal = false;
    double divisor = 1;

    while (!exit && next()) {
        switch (curChar) {
            case '.': decimal = true; break;
            case ',':
                /* ignored for separating purpose */
                break;
            case '0' ... '9':
                if (!decimal) num *= 10;
                else
                    divisor /= 10;

                num += divisor * (curChar - '0');
                break;
            default: exit = true; break;
        }
    }

    return num;
}

Token Lexer::makeVarOrKeyword() {
    std::string txt;
    txt += curChar;
    bool exit = false;
    while (!exit && next()) {
        switch (curChar) {
            case '-':
            case '_':
            case '0' ... '9':
            case 'a' ... 'z':
            case 'A' ... 'Z': txt += curChar; break;
            default: exit = true; break;
        }
    }
    if(KEYWORDS.find(txt) != KEYWORDS.end())
        return Token{KEYWORDS.at(txt)};
    return Token{Token::TkType::variable, txt};
}

Token Lexer::makeString() {
    std::string txt;
    bool exit = false;
    bool escaped = false;
    char starter = curChar;

    while (!exit && next()) {
        switch (curChar) {
            case '\\':  // escape character
                if (!escaped) {
                    escaped = true;
                } else {
                    txt += '\\';
                    escaped = false;
                }
                break;

            case '\'':
                if (!escaped && starter == '\'') {
                    exit = true;
                } else {
                    txt += '\'';
                    escaped = false;
                }
                break;

            case '\"':
                if (!escaped && starter == '\"') {
                    exit = true;
                } else {
                    txt += '\"';
                    escaped = false;
                }
                break;

            default:
                txt += curChar;
                escaped = false;
                break;
        }
    }

    return Token{Token::TkType::string_lit, txt};
}

void Lexer::ignoreComments(){
    bool star = false;
    while(next()){
        if (curChar == '*')
            star = true;
        else if (curChar == ')' && star)
            return;
        else 
            star = false;
    }
}

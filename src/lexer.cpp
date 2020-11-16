#include "lexer.hpp"

#include <fstream>
#include <iostream>
#include <string>

std::vector<Token> lex(std::ifstream &file) {
    std::vector<Token> tokens = {};
    char c;
    while (file.get(c)) {
        switch (c) {
            case '0' ... '9': tokens.push_back(makeNumber(file, c)); break;
            case 'a' ... 'z':
            case 'A' ... 'Z':
                tokens.push_back(makeVarOrKeyword(file, c));
                break;
            case '\'':
            case '"': tokens.push_back(makeString(file, c)); break;
            case '+': tokens.push_back(Token{Token::TkType::plus}); break;
            default: break;
        }
    }
    return tokens;
}

Token makeNumber(std::ifstream &file, char c) {
    double num = 0.;
    if (c == '0') {  // special cases (binary hexadecimal octal ...)
        file.get(c);
        switch (toupper(c)) {
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
    } else if (c >= '1' && c <= '9') {
        num = readDecimal(file, c);
    } else {
        // should be an error
    }

    return Token{Token::TkType::number_lit, num};
}

double readDecimal(std::ifstream &file, char c) {
    double num = c - '0';
    bool exit = false;
    bool decimal = false;
    double divisor = 1;

    while (!exit && file.get(c)) {
        switch (c) {
            case '.': decimal = true; break;
            case ',':
                /* ignored for separating purpose */
                break;
            case '0' ... '9':
                if (!decimal) num *= 10;
                else
                    divisor /= 10;

                num += divisor * (c - '0');
                break;
            default: exit = true; break;
        }
    }

    return num;
}

Token makeVarOrKeyword(std::ifstream &file, char c) {
    std::string txt;
    txt += c;
    bool exit = false;
    while (!exit && file.get(c)) {
        switch (c) {
            case '-':
            case '_':
            case '0' ... '9':
            case 'a' ... 'z':
            case 'A' ... 'Z': txt += c; break;
            default: exit = true; break;
        }
    }

    return Token{Token::TkType::variable, txt};
}

Token makeString(std::ifstream &file, char starter) {
    std::string txt;
    bool exit = false;
    bool escaped = false;
    char c;

    while (!exit && file.get(c)) {
        switch (c) {
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
                txt += c;
                escaped = false;
                break;
        }
    }

    return Token{Token::TkType::string_lit, txt};
}

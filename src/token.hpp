#pragma once

#include <string>

struct Token {
    enum struct TokenType {
        number_lit,
        string_lit,
        variable,
        plus,
	minus,
	star,
	slash,
	percent,
	equal,
	greater_than,
	less_than,
	greater_equal,
	less_equal,
	not_equal,
	quotes,
	colon,
	r_paren,
	l_paren,
	and_kw,
	or_kw,
	not_kw,
	print_kw,
	read_kw,
	goto_kw,
	let_kw,
	if_kw,
	else_kw
    };
    TokenType tag;

    union {
        double number;
        std::string text;
    };
    
    Token(TokenType type);
    Token(TokenType type, double nb);
    Token(TokenType type, std::string str);
    
    Token& operator=(const Token&);
    Token(const Token&);
    
    ~Token();
};

#pragma once

#include <string>

union TokenValue {
	std::string text;
	double number;
};

enum TokenType {
	number,
	string,
	var,
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
	goto_kw,
	let_kw,
	read_kw,
	if_kw,
	else_kw
};

struct Token {
	TokenType tag;
	TokenValue content;
};

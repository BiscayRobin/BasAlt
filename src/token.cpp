#include "token.hpp"

using namespace std;

Token::Token(TokenType type) { this->tag = type; }

Token::Token(TokenType type, double nb) {
    this->tag = type;
    this->number = nb;
}

Token::Token(TokenType type, string str) {
    this->tag = type;
    this->text = str;
}

Token& Token::operator=(const Token& elt) {
    if ((tag == TokenType::string_lit || tag == TokenType::variable) &&
        (elt.tag == TokenType::string_lit || elt.tag == TokenType::variable)) {
        text = elt.text;
        return *this;
    }
    if (tag == TokenType::string_lit) {
        text.~string();
    }

    switch (elt.tag) {
        case TokenType::number:
            number = elt.number;
            break;
        case TokenType::variable:
        case TokenType::string_lit:
            new (&text) string(elt.text);
            break;
        default:
            break;
    }
    tag = elt.tag;
    return *this;
}

Token::Token(const Token& elt) {
	tag = elt.tag;
	if(tag == TokenType::string_lit || tag == TokenType::variable) {
		new (&text) string(elt.text);
	}
	if(tag == TokenType::number) {
		number = elt.number;
	}
}

Token::~Token() {
    if (tag == TokenType::string_lit) text.~string();
}

#include "token.hpp"

using namespace std;

Token::Token(TkType type) : tag(type) {}

Token::Token(TkType type, double nb) : tag(type), number(nb) {}

Token::Token(TkType type, string str) : tag(type), text(str) {}

Token &Token::operator=(const Token &elt) {
    if ((tag == TkType::string_lit || tag == TkType::variable) &&
        (elt.tag == TkType::string_lit || elt.tag == TkType::variable)) {
        text = elt.text;
        return *this;
    }
    if (tag == TkType::string_lit || tag == TkType::variable) {
        text.~string();
    }

    switch (elt.tag) {
    case TkType::number_lit:
        number = elt.number;
        break;
    case TkType::variable:
    case TkType::string_lit:
        new (&text) string(elt.text);
        break;
    default:
        break;
    }
    tag = elt.tag;
    return *this;
}

Token::Token(const Token &elt) {
    tag = elt.tag;
    if (tag == TkType::string_lit || tag == TkType::variable) {
        new (&text) string(elt.text);
    }
    if (tag == TkType::number_lit) {
        number = elt.number;
    }
}

Token::~Token() {
    if (tag == TkType::string_lit || tag == TkType::variable) {
        text.~string();
    }
}

std::ostream &operator<<(std::ostream &os, const Token &tk) {
    static const std::string
        TOKEN_NAMES[static_cast<int>(Token::TkType::ENUM_SIZE)] = {
            [static_cast<int>(Token::TkType::number_lit)] = "num",
            [static_cast<int>(Token::TkType::plus)] = "plus",
            [static_cast<int>(Token::TkType::string_lit)] = "str",
            [static_cast<int>(Token::TkType::variable)] = "var",
        };
    os << "<Tk: " << TOKEN_NAMES[static_cast<int>(tk.tag)] << " >";

    if (tk.tag == Token::TkType::number_lit) {
        os.precision(17);
        os << '(' << tk.number << ')';
    }
    if (tk.tag == Token::TkType::variable ||
        tk.tag == Token::TkType::string_lit) {
        os << '(' << tk.text << ')';
    }
    return os;
}

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
            [static_cast<int>(Token::TkType::line_sep)] = "l_sep",
            [static_cast<int>(Token::TkType::and_kw)] = "and",
            [static_cast<int>(Token::TkType::or_kw)] = "or",
            [static_cast<int>(Token::TkType::not_kw)] = "not",
            [static_cast<int>(Token::TkType::if_kw)] = "if",
            [static_cast<int>(Token::TkType::else_kw)] = "else",
            [static_cast<int>(Token::TkType::read_kw)] = "read",
            [static_cast<int>(Token::TkType::print_kw)] = "print",
            [static_cast<int>(Token::TkType::goto_kw)] = "goto",
            [static_cast<int>(Token::TkType::let_kw)] = "let",
            [static_cast<int>(Token::TkType::l_paren)] = "l_par",
            [static_cast<int>(Token::TkType::r_paren)] = "r_par",
            [static_cast<int>(Token::TkType::colon)] = "colon",
            [static_cast<int>(Token::TkType::slash)] = "slash",
            [static_cast<int>(Token::TkType::star)] = "star",
            [static_cast<int>(Token::TkType::minus)] = "minus",
            [static_cast<int>(Token::TkType::percent)] = "percent",
            [static_cast<int>(Token::TkType::equal)] = "equal",
            [static_cast<int>(Token::TkType::greater_equal)] = "ge",
            [static_cast<int>(Token::TkType::greater_than)] = "gt",
            [static_cast<int>(Token::TkType::less_equal)] = "le",
            [static_cast<int>(Token::TkType::less_than)] = "lt",
            [static_cast<int>(Token::TkType::not_equal)] = "ne",
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

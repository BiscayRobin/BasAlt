#pragma once

#include <ostream>
#include <string>

struct Token {
    enum class TkType {
        and_kw,
        colon,
        else_kw,
        equal,
        goto_kw,
        greater_equal,
        greater_than,
        if_kw,
        l_paren,
        less_equal,
        less_than,
        let_kw,
        minus,
        not_equal,
        not_kw,
        number_lit,
        or_kw,
        percent,
        plus,
        print_kw,
        quotes,
        r_paren,
        read_kw,
        slash,
        star,
        string_lit,
        variable,
        ENUM_SIZE,
    };
    TkType tag;

    union {
        double number;
        std::string text;
    };

    Token(TkType type);
    Token(TkType type, double nb);
    Token(TkType type, std::string str);

    Token &operator=(const Token &);
    Token(const Token &);
    friend std::ostream &operator<<(std::ostream &os, const Token &t);

    ~Token();
};

std::ostream &operator<<(std::ostream &os, const Token &t);

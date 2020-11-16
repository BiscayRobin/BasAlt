#include <iostream>

#include "../libs/CLI11.hpp"
#include "lexer.hpp"
#include "token.hpp"

int main(int argc, char **argv) {
    CLI::App app{"Interpreter for a BASIC Alternative"};

    std::string filename = "";

    app.add_option("file", filename, "File to interpret from")->required();

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << "." << std::endl;
    }

    std::cout << "lexing..." << std::endl;

    // lex it
    auto tokens = lex(file);

    for (auto tok : tokens) {
        std::cout << tok << std::endl;
    }

    file.close();

    return 0;
}

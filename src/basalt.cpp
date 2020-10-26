#include <iostream>

#include "../libs/CLI11.hpp"

int main(int argc, char **argv){
	
	CLI::App app{"Interpreter for a BASIC Alternative"};

	std::string filename = "";

	app.add_option("file",
			filename,
			"File to interpret from")->required();

	try {
		app.parse(argc,argv);
	} catch (const CLI::ParseError &e) {
		return app.exit(e);
	}

	return 0;
}	

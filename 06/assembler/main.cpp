#include "parser.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr << "Expected a file";
		return 1;
	}	
	else if(argc > 2)
	{
		std::cerr << "We expected only one argument";
		return 1;
	}

	std::string target_file = argv[1];


	std::ifstream input;
	input.open(target_file);

	if(!input)
	{
		std::cerr << "File: " << target_file << " does not exist\n";
		return 1;
	}
	first_pass(input);
	printTable();
//	parse(input);
}

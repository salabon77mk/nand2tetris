#include <string>
#include <iostream>
#include "parser.hpp"
#include "writer.hpp"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr << "Expected a file";
		return 1;
	}

	for(int i = 1; i < argc; ++i)
	{
		std::string target_file = argv[i];
		std::ifstream input(target_file);

		if(!input)
		{
			std::cerr << "File: " << target_file << " doest not exit, exiting\n";
			return 1;
		}
		std::string delim = ".";
		std::string outfile_name = target_file.substr(0, target_file.find(delim));
		outfile_name += ".asm";
		Writer writer(outfile_name);
		parse(input, writer);
	}
}

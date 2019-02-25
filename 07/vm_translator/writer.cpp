#include <string>
#include <fstream>
#include <array>
#include "writer.hpp"


Writer::Writer(std::string& str):outfile(str) {}

Writer::~Writer()
{
	this->outfile.close();
}

void Writer::arithmetic(std::string& str)
{
}

void Writer::pushPop(std::string& str)
{

}

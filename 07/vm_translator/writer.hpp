#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <string>


class Writer
{
private:
	std::ofstream outfile; // set to null in cpp file
	Writer();
public:
	static void arithmetic(std::string& str);
	static void pushPop(std::string& str);
	~Writer();
	Writer(std::string& str);
};

#endif

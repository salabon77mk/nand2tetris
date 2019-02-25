#include "parser.hpp"
#include <string>
#include <fstream>
#include <unordered_set>
#include <cctype>

#include <iostream>

enum CommandType
{
	ARITHMETIC,
	PUSH,
	POP,
	LABEL,
	GOTO,
	IF,
	FUNCTION,
	RETURN,
	CALL
};

static std::string getNextLine(std::ifstream& file);
static bool isComment(std::string& currLine);
static inline void trim(std::string& str);

static enum CommandType getCommandType(const std::string& currLine);
static std::string getFirstWord(const std::string& currLine);

void parse(std::ifstream& file, Writer& outfile_name)
{
	std::string currLine = "";

	while((currLine = getNextLine(file)).length() > 0)
	{
		std::cout << currLine << "\n";
		unsigned int i = 0;
		unsigned int& index = i;
		enum CommandType commType = getCommandType(currLine);


	}
}

static std::string getNextLine(std::ifstream& file)
{
	std::string currLine = "";
	
	if(std::getline(file, currLine))
	{
		trim(currLine);
		while((currLine.length() == 0 || isComment(currLine)) && file)
		{
			std::getline(file, currLine);
			trim(currLine);
		}
	}

	return (!file) ? "" : currLine;
}


// Only checks if a line STARTS as a comment
static bool isComment(std::string& currLine)
{
	if(currLine.length() > 2)
	{
		std::string first_two = currLine.substr(0, 2);

		return (first_two == "//") ? true : false;
	}
	return false;
}

static inline void trim(std::string& str)
{
	unsigned int i = 0;
	for( ; i < str.length() && (str[i] == ' ' || str[i] == '\t') ; ++i){}
	str =  str.substr(i, str.length());
}

static enum CommandType getCommandType(const std::string& currLine)
{
	const std::unordered_set<std::string> arithmetic_ops
	{"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};
	const std::string push = "push";
	const std::string pop = "pop";
	
	std::string firstWord = getFirstWord(currLine);
	std::cout << firstWord << "\n";
	auto it = arithmetic_ops.find(firstWord);

	if(it != arithmetic_ops.end()) { return ARITHMETIC; }
	else if(firstWord == push) { return PUSH; }	
	else if(firstWord == pop) { return POP; }

}

static std::string getFirstWord(const std::string& currLine)
{
	std::string firstWord = "";
	// - incase it is if-goto keyword
	for(unsigned int i = 0; i < currLine.length() && (isalpha(currLine[i]) || currLine[i] == '-'); ++i)
	{
		firstWord += currLine[i];
	}	
	return firstWord;
}

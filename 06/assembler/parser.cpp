#include "parser.hpp"
#include <string>
#include <fstream>
#include <cctype>

#include <iostream>
enum Command_Type { A_COMMAND, C_COMMAND };

static void skipSugar(std::ifstream& file, std::string& currLine);
static bool isComment(std::string& currLine);

static int extractNum(std::string& str);
static std::string binToDec(int dec);
static enum Command_Type getType(std::string& str);

inline void aCommErr(std::string& str);

void parse(std::ifstream& file)
{
	std::string currLine;
	while(std::getline(file, currLine))
	{
		// Skip blank lines and comments
		skipSugar(file, currLine);

		if(!file)
		{
			return;
		}

		std::cout << currLine << "\n";

		enum Command_Type curr_comm_type = getType(currLine);
		std::cout << curr_comm_type << "\n";
	}

}

void skipSugar(std::ifstream& file, std::string& currLine)
{
	while((currLine.length() == 0 || isComment(currLine)) && file)
	{
		std::getline(file, currLine);
	}	
}

bool isComment(std::string& currLine)
{
	if(currLine.length() > 2)
	{
		std::string first_two = currLine.substr(0, 2);
		if(first_two == "//")
		{
			return true;
		}
		return false;
	}
	return false;
}

enum Command_Type getType(std::string& str)
{
	if(str[0] == '@')
	{
		return A_COMMAND;
	}
	if(std::isalpha(str[0]))
		{
		return C_COMMAND;
		}			
		
		std::cerr << "String: " << str << "is not an A or C command";
		exit(-1);
}

// Once we've seen an A-command, convert it into an int
// for further processing in binToDec
int extractNum(std::string& str)
{
	std::string numbers = "";
	int i = 1;
	
	while(i < str.length() && std::isdigit(str[i]))
	{
		numbers += str[i];
		++i;
	}

	// no longer dealing with digits
	while(i < str.length())
	{
		if(str[i] == ' '){}
		else if(str[i] == '/')
		{
			try
			{
				// peak ahead to see if it's a comment
				if(str[++i] == '/')
				{
					break;
				}
				else
				{
					aCommErr(str);	
				}
			}
			catch(std::out_of_range& err)
			{
				aCommErr(str);
			}
		}
		else
		{
			aCommErr(str);
		}
		++i;
	}
	int num = std::stoi(numbers);
	return num;
}

inline void aCommErr(std::string& str)
{
	std::cerr << "A-command: " << str << " has extra symbols. Should just be @ffffff";
	exit(-1);
}

std::string binToDec(int dec)
{	
	if(dec >= 32768)
 	{
		std::cerr << "Overflow on A value";
		exit(-1);
    }

	if(dec < 0)
	{
		std::cerr << "Negative constants are not allowed";
		exit(-1);
    }
  
  std::string binRep = "000000000000000";

  //check if negative
  int currCeiling = 16384;

  for(int i = 0; i < 15; i++)
  {
	if(dec >= currCeiling)
	{
		binRep[i] = '1';
		dec = dec - currCeiling;
	}
	currCeiling >>= 1;
  }

  return binRep;
}

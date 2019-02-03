#include "parser.hpp"
#include "tables.hpp"
#include <string>
#include <fstream>
#include <cctype>
#include <memory>

#include <vector>

#include <iostream>
enum Command_Type { A_COMMAND, C_COMMAND, LABEL_SYM, VARIABLE_SYM };

struct C_Comm_Strings
{
	std::string dest_str = "";
	std::string comp_str = "";
	std::string jmp_str = "";
};

static std::unique_ptr<C_Comm_Strings> parseCComm(std::string& currLine);

inline static void nonInstrSkip(std::ifstream& file, std::string& currLine);
static void skipSugar(std::ifstream& file, std::string& currLine);
static bool isComment(std::string& currLine);

static void checkSyntax(std::string& currLine, int index);
static bool checkInlineComm(std::string& currLine, int index);

static int extractNum(std::string& str);
static enum Command_Type getType(std::string& str);

inline void handleLabel(std::string& currLine);
void handleVariable(std::string& currLine);
inline void syntaxErr(std::string& str);

void handleVariable(std::ifstream& file, std::string& currLine)
{
	std::string var = ""; // contains the variable symbol we will use
    int i = 1;
	for( ; i < currLine.length() && std::isalnum(currLine[i]))
	{
		var += currLine[i];
	}
	checkSyntax(currLine, i);

	std::string val = Table::getSymVal(var);
	if(val.length() != 0)
	{
		// print to file
	}
	else if(val.length() == 0)
	{
		Table::addVarSym(var);
		// do a lookup again and print it to file
		val = Table::getSymVal(var);
		// print contents to file appended with 0
	}
}

inline void handleLabel(std::string& currLine)
{

	// Make a check that the symbol is syntax good
	std::string label = "";
	int i = 1;
	bool right_paren = false; // have not detected the right paren yet
	for( ; i < currLine.length() && !right_paren; ++i)
	{
		if(currLine.at(i) != ')')
		{
			label += currLine.at(i);
		}
		else
		{
			right_paren = true;
		}
	}
	// Then add it
	if(right_paren)
	{
		checkSyntax(currLine, i);
		labels.push_back(label);
	    if(Table::getSymVal(label).length != 0) // symbol is not in table, add it
		{	
			Table::addLabelSym(label, instr_count);
		}
	}
}

std::vector<std::string> labels;
void printTable()
{
	auto it = labels.begin();

	for( ; it != labels.end(); ++it)
	{
		std::string sym = Table::getSymVal(*it);
		std::cout << "Label: " << *it << "\nSym: " << sym << "\n";
	}
}

void first_pass(std::ifstream& file)
{
	int instr_count = 0; // number of Hack instructions encountered
	std::string currLine = "";

	while(std::getline(file, currLine))
	{
		nonInstrSkip(file, currLine);
		enum Command_Type comm_type = getType(currLine);

		// If it's any kind of instruction, we just increment instr_count
		if(comm_type == A_COMMAND 
				|| comm_type == C_COMMAND 
				|| comm_type == VARIABLE_SYM)
		{
			instr_count++;
		}
		else if(comm_type == LABEL_SYM)
		{
			handleLabel(currLine);
		}
	}
}


void parse(std::ifstream& file)
{
	std::string currLine = "";
	while(std::getline(file, currLine))
	{
		// Skip blank lines and comments
		nonInstrSkip(file, currLine);

		std::cout << currLine << "\n";

		enum Command_Type comm_type = getType(currLine);
		if(comm_type == A_COMMAND)
		{
			int num = extractNum(currLine);
			std::string bin_rep = binToDec(num);
			// TODO print to file bin_rep
		}
		else if(comm_type == C_COMMAND)
		{
			// CHANGE VAR NAME
			std::unique_ptr<C_Comm_Strings> s = parseCComm(currLine);
			std::cout << s->dest_str << "\n" << s->comp_str << "\n" << s->jmp_str << "\n";			
		}
		else if(comm_type == VARIABLE_SYM)
		{

		}
	}

}

inline static void nonInstrSkip(std::ifstream& file, std::string& currLine)
{
	skipSugar(file, currLine);
	if(!file) {return;}
}

void skipSugar(std::ifstream& file, std::string& currLine)
{
	while((currLine.length() == 0 || isComment(currLine)) && file)
	{
		std::getline(file, currLine);
	}	
}

// Only checks if a line STARTS as a comment
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

bool checkInlineComm(std::string& currLine, int index)
{
	try
	{
		// peak ahead to see if it's a comment
		if(currLine[++index] == '/')
		{
			return true;
		}
		else
		{
			return false;	
		}
	}
	catch(std::out_of_range& err)
	{
		syntaxErr(currLine);
	}
}

// makes sure there's no extra junk in the line
void checkSyntax(std::string& currLine, int index)
{
	while(index < currLine.length())
	{
		if(currLine[index] == ' '){} // Do nothing, ignore white space
		else if(currLine[index] == '/')
		{
			bool isComm = checkInlineComm(currLine, index);
			if(isComm)
			{ 
				return; 
			} // ignore everything else 
			syntaxErr(currLine);
		}
		else
		{
			syntaxErr(currLine);
		}
		++index;
	}
}

enum Command_Type getType(std::string& str)
{
	// Each command must be at least two chars long in Hack
	if(str.length() > 1)
	{
		if(str[0] == '@')
		{
			if(std::isdigit(str[1])) { return A_COMMAND; }
			else if(std::isalpha(str[1])) { return VARIABLE_SYM; }
			else { syntaxErr(str); } // Non alpha-num is syntax err
		}
		else if(std::isalpha(str[0]))
		{
			return C_COMMAND;
		}	
		else if(str[0] == '(')
		{
			return LABEL_SYM;
		}	
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
	checkSyntax(str, i);

	int num = std::stoi(numbers);
	return num;
}

inline void syntaxErr(std::string& str)
{
	std::cerr << "Line: " << str << " has a syntax error" << "\n";
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

// Parse a C command
static std::unique_ptr<C_Comm_Strings> parseCComm(std::string& currLine)
{
	bool equal_flag = false;	// Set to true if an '=' is found in currLine
	bool semi_flag = false;		// Set to true if a ';' is found in currLine

	auto parsed_comm = std::make_unique<C_Comm_Strings>();

	// We fill out the comp_str first, if we find an =, we reassign the contents of comp_str to dest_str	
	int i = 0;
	for(; i < currLine.length() && (currLine[i] != ' ' || currLine[i] != '/'); i++)
	{
		bool special_char = false;	// Set to true if either '=' or ';' found
		if(currLine[i] == '=')
		{
			parsed_comm->dest_str = parsed_comm->comp_str;
			parsed_comm->comp_str = "";
			special_char = true;
		}

		if(currLine[i] == ';')
		{
			semi_flag = true;
			special_char = true;
		}

		if(!special_char)
		{
			if(semi_flag)
			{
				parsed_comm->jmp_str += currLine[i];
			}
			else
			{
				parsed_comm->comp_str += currLine[i];	
			}
		}
	}
	checkSyntax(currLine, i);
	return parsed_comm;
}

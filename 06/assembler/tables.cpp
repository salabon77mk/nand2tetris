#include <unordered_map>
#include <string>
#include <iostream>
#include "tables.hpp"
#include "parser.hpp"
int Table::addr = 16;

std::unordered_map<std::string, std::string> Table::j_map =
{
	// Empty string represents null in the Hack specs
	{"", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"}, 
    {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}	
};

std::unordered_map<std::string, std::string> Table::d_map =
{
		{"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"}, 
	    {"A", "100"}, {"AM", "101"}, {"AD", "110"}, {"AMD", "111"}
};

std::unordered_map<std::string, std::string> Table::c_map =
{
	{"0", "0101010"}, {"1", "0111111"}, {"-1", "0111010"}, {"D", "0001100"}, 		
	{"A", "0110000"}, {"!D", "0001101"}, {"!A", "0110001"}, {"-D", "0001111"}, 	
	{"-A", "0110011"}, {"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"}, 		
	{"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"}, {"A-D", "0000111"}, 	
	{"D&A", "0000000"}, {"D|A", "0010101"},
 	{"M", "1110000"}, {"!M", "1110001"}, {"-M", "1110011"}, {"M+1", "1110111"},  	
 	{"M-1", "1110010"}, {"D+M", "1000010"}, {"D-M", "1010011"}, {"M-D", "1000111"},  	
   	{"D&M", "1000000"}, {"D|M", "1010101"}  
};

std::unordered_map<std::string, std::string> Table::sym_map =
{
	{"R0", "000000000000000"}, {"R1","000000000000001"}, {"R2","000000000000010"}, {"R3","000000000000011"},
	// change r4 and r5 TODO
   	{"R4", "000000000000100"}, {"R5", "000000000000101"}, {"R6", "000000000000111"}, {"R7", "000000000001000"}, 
	{"R8", "000000000001001"}, {"R9", "000000000001010"}, {"R10", "000000000001011"}, {"R11", "000000000001100"}, 
	{"R12", "000000000001101"}, {"R13", "000000000001110"}, {"R14", "000000000001111"}, {"R15", "000000000010000"}, 
	{"SP", "000000000000000"}, {"LCL", "000000000000001"}, {"ARG", "000000000000010"}, {"THIS", "000000000000011"},
   	{"THAT", "000000000000100"}, {"SCREEN", "010000000000000"}, {"KBD", "110000000000000"}
};


std::string Table::getJBits(const std::string& key)
{
	auto iter = Table::j_map.find(key);
	if(iter != Table::j_map.end())
	{
		return iter->second;
	}
	else if(iter == Table::j_map.end())
	{
		std::cout << "Key not found: " << key << std::endl;
		return ""; // handle empty string in main
	}
}

std::string Table::getDBits(const std::string& key)
{

}

std::string Table::getCBits(const std::string& key)
{

}


void Table::addVarSym(const std::string& key)
{
	std::string val = binToDec(addr);
    Table::sym_map.insert({key, val});
	// incr after insert
	++addr;
}


void Table::addLabelSym(const std::string& key, int value)
{
	std::string val = binToDec(value);
	Table::sym_map.insert({key, val});
}

std::string Table::getSymVal(const std::string& key)
{	
	auto it = Table::sym_map.find(key);
	if(it != Table::sym_map.end())
	{
		return it->second;
	}
	else if(it == Table::sym_map.end())
	{
		std::cout << "Key not found: " << key << std::endl;
		return ""; // handle empty string in main
	}
}

#ifndef TABLES_H
#define TABLES_H

#include <unordered_map>
#include <string>

class Table
{
private:	
	static std::unordered_map<std::string, std::string> j_map; 
	static std::unordered_map<std::string, std::string> d_map; 
	static std::unordered_map<std::string, std::string> c_map;
	static std::unordered_map<std::string, std::string> sym_map;
	Table();
public:
	static std::string getJBits(const std::string& key);
	static std::string getDBits(const std::string& key);
	static std::string getCBits(const std::string& key);
};

#endif
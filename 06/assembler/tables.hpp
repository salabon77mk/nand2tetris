#ifndef TABLES_H
#define TABLES_H

#include <unordered_map>
#include <string>

class Table
{
private:
	static int addr;	
	static std::unordered_map<std::string, std::string> j_map; 
	static std::unordered_map<std::string, std::string> d_map; 
	static std::unordered_map<std::string, std::string> c_map;
	static std::unordered_map<std::string, std::string> sym_map;
	static std::string get(const std::unordered_map<std::string, std::string>& map, const std::string& key);
	Table();
public:
	static std::string getJBits(const std::string& key);
	static std::string getDBits(const std::string& key);
	static std::string getCBits(const std::string& key);
	static void addLabelSym(const std::string& key, int value);
	static std::string getSymVal(const std::string& key);
	static void addVarSym(const std::string& key);
};

#endif

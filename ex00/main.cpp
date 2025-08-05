#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <limits>

typedef struct s_date{
	int year;
	int month;
	int day;
}	t_date;

void fillMap(std::map<std::string, float> &map, std::ifstream &infile){
	std::string ph;
	float s;
	size_t pos;
	std::string value;
	std::string date;
	while (getline(infile, ph))
	{
		if (ph.empty() || ph == "data | value" || ph == "date,exchange_rate")
			continue;
		date = ph.substr(0, 10);
		if (ph.find("|") < ph.size())
			value = ph.substr(ph.find("| ") + 1, ph.size() - 12);
		else if (ph.find(",") < ph.size())
			value = ph.substr(ph.find(",") + 1, ph.size() - 11);
		else
			continue;
		try{
			s = stof(value, &pos);
		} catch (std::exception &e){
			//
		}
		if (s > std::numeric_limits<float>::max() || s < std::numeric_limits<float>::min())
			continue;
		map.insert(std::make_pair(ph.substr(0, 10), s));
	}
	infile.close();
}

#include <string>
#include <regex>

bool checkInput(const std::string& line) {
	static const std::regex pattern(R"(^(\d{4})-(\d{2})-(\d{2}) \| -?\d+(\.\d+)?$)");
	std::smatch m;
	if (!std::regex_match(line, m, pattern)) return false;
	int year  = std::stoi(m[1]);
	int month = std::stoi(m[2]);
	int day   = std::stoi(m[3]);
	if (month < 1 || month > 12) return false;
	int dim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	if (leap) dim[1] = 29;
	if (day < 1 || day > dim[month-1]) return false;
	return true;
}


int main(int ac, char **av){
	BitcoinExchange btc;

	if (ac != 2)
		return (std::cout << "Wrong number of arguemnst\n", 1);
	try{
		std::ifstream bitcoinDB("test/data.csv");
		btc.exchange(bitcoinDB, av[1]);
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}
}
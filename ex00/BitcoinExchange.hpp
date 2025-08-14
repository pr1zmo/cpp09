#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <exception>
#include <map>
#include <limits>
#include <cctype>

class BitcoinExchange {
	private:
		std::ifstream _dataSet;
		std::ifstream _inputData;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		int checkLimits(float rit, float it);
		bool checkInput(const std::string& line);
		void fillMap(std::map<std::string, float> &map, std::ifstream &infile);
		void exchange(std::ifstream &infile, const std::string &inputFile);
};

#endif
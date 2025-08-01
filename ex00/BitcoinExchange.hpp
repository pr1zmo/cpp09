#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <map>

class BitcoinExchange {
	private:
		std::ifstream _dataSet;
		std::string _inputTxt;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		int parseLine(std::string line);
		// int parseTxtFile(std::ofstream file);
		void listPrices(std::ifstream &dataSet, std::string const &inputTxt);
		int checkFiles(std::ifstream &dataSet, const std::string &inputTxt);
};

#endif
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

class BitcoinExchange {
	private:
		std::ifstream _dataSet;
		std::ifstream _inputData;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		int parseLine(std::string line);
		// int parseTxtFile(std::ofstream file);
		void listPrices(std::map<std::string, float>&bitcoinMap, std::map<std::string, std::string>&inputList);
		int checkFiles(const std::string& dbFile, const std::string &inputTxt);
		int checkLimits(float rit, float it);
		void exchange(std::ifstream &data, const std::string &inputTxt);
};

#endif
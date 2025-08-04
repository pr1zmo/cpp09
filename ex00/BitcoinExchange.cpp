#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		//
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

void findClosestDate(std::map<std::string, double>bitcoin, std::string line){
	(void)bitcoin;
	std::string date = line.substr(0, 10);
	std::cout << line << std::endl;
}

void BitcoinExchange::listPrices(std::map<std::string, double>&bitcoinMap, std::map<std::string, std::string>&inputList){
	// std::map<std::string, double> bitcoin;
	// std::map<std::string, std::string> inputLine;

	// std::ifstream file(inputTxt);
	// if (!file.is_open()){
	// 	std::cerr << "Error: Could not open file " << inputTxt << std::endl;
	// }
	// else{
	// 	std::string line;
	// 	int i = 0;
	// 	while (std::getline(file, line)){
	// 		inputLine.insert({std::to_string(i), line});
	// 		i++;
	// 	}
	// }
	// for (const auto& pair : inputLine){
	// 	findClosestDate(bitcoin, pair.second);
	// }
}

int BitcoinExchange::checkFiles(const std::string& dbFile, const std::string& inputTxt){
	// dbFile.open("test/data.csv");
	// inputTxt.open(std::string("test/") + av[1]);
	return 1;
}

std::map<std::string, double> setBitcoin(std::ifstream& dataSet){
	//
	std::map<std::string, double> rv;
	//
	return rv;
}

std::map<std::string, std::string> setInput(std::ifstream& inputData){
	std::map<std::string, std::string> rv;
	//
	return rv;
}

int BitcoinExchange::parseLine(std::string line){
	std::map<std::string, double> bitcoinMap; // needs to be *std::map<std::string, std::string>bitcoinMap to hold an entire line.
	std::map<std::string, std::string> inputMap;
	bitcoinMap = setBitcoin(this->_dataSet);
	inputMap = setInput(this->_inputData);
	listPrices(bitcoinMap, inputMap);
	return (0);
}
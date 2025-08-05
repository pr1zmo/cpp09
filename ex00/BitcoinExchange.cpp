#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
	//
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

void findClosestDate(std::map<std::string, float>bitcoin, std::string line){
	(void)bitcoin;
	std::string date = line.substr(0, 10);
	std::cout << line << std::endl;
}

void BitcoinExchange::listPrices(std::map<std::string, float>&bitcoinMap, std::map<std::string, std::string>&inputList){

}

int BitcoinExchange::checkFiles(const std::string& dbFile, const std::string& inputTxt){
	return 1;
}

std::map<std::string, float> setBitcoin(std::ifstream& dataSet){
	//
	std::map<std::string, float> rv;
	//
	return rv;
}

std::map<std::string, std::string> setInput(std::ifstream& inputData){
	std::map<std::string, std::string> rv;
	//
	return rv;
}

int BitcoinExchange::parseLine(std::string line){
	std::map<std::string, float> bitcoinMap;
	std::map<std::string, std::string> inputMap;
	bitcoinMap = setBitcoin(this->_dataSet);
	inputMap = setInput(this->_inputData);
	listPrices(bitcoinMap, inputMap);
	return (0);
}

int BitcoinExchange::checkLimits(float rit, float it) {
	float product = it * rit;
	float max_int = static_cast<float>(std::numeric_limits<int>::max());
	float min_int = static_cast<float>(std::numeric_limits<int>::min());

	if (product != product) {
		return 0;
	}

	if (product > max_int || product < min_int) {
		return 0;
	}
	return 1;
}

// void BitcoinExchange::exchange(){
// 	if (!bitcoinDB.is_open()) {
// 		std::cerr << "Error: Could not open file test/data.csv\n";
// 		return 1;
// 	}
// }
#include "BitcoinExchange.hpp"

	Bitcoin::Bitcoin(std::string &argv)
	: _inputFile(argv) {
	}

Bitcoin::Bitcoin(const Bitcoin& other)
{
	*this = other;
}

Bitcoin& Bitcoin::operator=(const Bitcoin& other) {
	if (this != &other) {
		//
	}
	return *this;
}

Bitcoin::~Bitcoin() {
}

bool Bitcoin::checkFiles(const std::string &argv){
	std::ifstream inputFile;

	this->_data.open("data.csv");
	if (!this->_data.is_open() || this->_data.eof())
		return (std::cerr << "error with data.csv\n", 1);	
	
	inputFile.open(argv.c_str());
	if (!inputFile.is_open())
		return (std::cerr << "Couldn't open file: " << argv << std::endl, false);

	fillMap(this->_btc, this->_data);
	this->_data.close();
	inputFile.close();
	return 1;
}

void Bitcoin::fillMap(std::map<std::string, float> &map, std::ifstream &infile){
	std::string ph;
	float s;
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
			s = std::atof(value.c_str());
		} catch (std::exception &e){
			//
		}
		if (s > std::numeric_limits<float>::max() || s < std::numeric_limits<float>::min())
			continue;
		map.insert(std::make_pair(ph.substr(0, 10), s));
	}

	infile.close();
}

/* bool Bitcoin::checkInput(const std::string& line) {
	if (line.size() < 14) return false;
	// YYYY-MM-DD | VALUE
	for (int i = 0; i < 4; ++i)
		if (!std::isdigit(line[i])) return false;
	if (line[4] != '-')
		return false;
	if (!std::isdigit(line[5]) || !std::isdigit(line[6]))
		return false;
	if (line[7] != '-')
		return false;
	if (!std::isdigit(line[8]) || !std::isdigit(line[9]))
		return false;
	if (line[10] != ' ' || line[11] != '|' || line[12] != ' ')
		return false;
	// parse date
	int year  = std::atoi(line.substr(0,4).c_str());
	int month = std::atoi(line.substr(5,2).c_str());
	int day   = std::atoi(line.substr(8,2).c_str());
	if (month < 1 || month > 12) return false;
	int dim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap = (year%4 == 0 && (year%100 != 0 || year%400 == 0));
	if (leap) dim[1] = 29;
	if (day < 1 || day > dim[month-1]) return false;
	// parse numeric value
	const std::string value = line.substr(13);
	if (value.empty()) return false;
	bool seenDot = false;

	for (size_t i = 0; i < value.size(); ++i) {
		char c = value[i];
		if (i == 0 && c == '-') {
			if (value.size() == 1) return false;
			continue;
		}
		if (c == '.') {
			if (seenDot) return false;
			seenDot = true;
			if (i+1 == value.size()) return false;
			continue;
		}
		if (!std::isdigit(c)) return false;
	}
	return true;
} */

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

bool Bitcoin::checkInput(const std::string& line) {
	if (line.size() < 14) {
		std::cerr << "Error: line too short (size " << line.size() << ")\n";
		return false;
	}
	// YYYY-MM-DD | VALUE
	for (int i = 0; i < 4; ++i) {
		if (!std::isdigit(line[i])) {
			std::cerr << "Error: expected digit at index[" << i << "] ('" << line[i] << "')\n";
			return false;
		}
	}
	if (line[4] != '-') {
		std::cerr << "Error: expected '-' at index[4] ('" << line[4] << "')\n";
		return false;
	}
	if (!std::isdigit(line[5])) {
		std::cerr << "Error: expected digit at index[5] ('" << line[5] << "')\n";
		return false;
	}
	if (!std::isdigit(line[6])) {
		std::cerr << "Error: expected digit at index[6] ('" << line[6] << "')\n";
		return false;
	}
	if (line[7] != '-') {
		std::cerr << "Error: expected '-' at index[7] ('" << line[7] << "')\n";
		return false;
	}
	if (!std::isdigit(line[8])) {
		std::cerr << "Error: expected digit at index[8] ('" << line[8] << "')\n";
		return false;
	}
	if (!std::isdigit(line[9])) {
		std::cerr << "Error: expected digit at index[9] ('" << line[9] << "')\n";
		return false;
	}
	if (line[10] != ' ' || line[11] != '|' || line[12] != ' ') {
		std::cerr << "Error: expected ' | ' at indices[10..12] ('" 
					<< line.substr(10,3) << "')\n";
		return false;
	}
	// parse date
	int year  = std::atoi(std::string(line, 0, 4).c_str());
	int month = std::atoi(std::string(line, 5, 2).c_str());
	int day   = std::atoi(std::string(line, 8, 2).c_str());
	if (month < 1 || month > 12) {
		std::cerr << "Error: month out of range at indices[5..6] (" << month << ")\n";
		return false;
	}
	int dim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap = (year%4 == 0 && (year%100 != 0 || year%400 == 0));
	if (leap) dim[1] = 29;
	if (day < 1 || day > dim[month-1]) {
		std::cerr << "Error: day out of range at indices[8..9] (" << day << ")\n";
		return false;
	}
	// parse numeric value
	const std::string value = line.substr(13);
	if (value.empty()) {
		std::cerr << "Error: missing numeric value after index[13]\n";
		return false;
	}
	bool seenDot = false;
	for (size_t i = 0; i < value.size(); ++i) {
		char c = value[i];
		if (i == 0 && c == '-') {
			if (value.size() == 1) {
					std::cerr << "Error: lone '-' at value index[" << 13+i << "]\n";
					return false;
			}
			continue;
		}
		if (c == '.') {
			if (seenDot) {
					std::cerr << "Error: multiple '.' at value index[" << 13+i << "]\n";
					return false;
			}
			seenDot = true;
			if (i+1 == value.size()) {
					std::cerr << "Error: trailing '.' at value index[" << 13+i << "]\n";
					return false;
			}
			continue;
		}
		if (!std::isdigit(c)) {
			std::cerr << "Error: invalid character '" << c << "' at value index[" << 13+i << "]\n";
			return false;
		}
	}
	return true;
}

void Bitcoin::displayRate(const std::string& line, std::map<std::string, float> &btc){
	std::map<std::string, float>::reverse_iterator it;
	for (it=btc.rbegin(); it!=btc.rend(); it++){
		if (it->first <= line)
			{
				std::cout << line.substr(0, 10) << " => ";
				std::cout << std::atof(line.substr(13).c_str()) << " = ";
				std::cout << it->second * std::atof(line.substr(13).c_str()) << std::endl;
				break;
			}
	}
}

bool numError(const std::string &line){
	const std::string value = line.substr(13);

	long long int x = std::atoll(value.c_str());
	if (x > std::numeric_limits<int>::max() || x < std::numeric_limits<int>::min())
		return (std::cerr << "Error: too large number\n", false);
	if (x < 0)
		return (std::cerr << "Error: Not a positive number\n", false);
	return true;
}

void Bitcoin::exchange(){
	std::string line;

	std::ifstream inputFile;
	if (!checkFiles(this->_inputFile)){
		std::cerr << "Could not open input file\n";
		return ;
	}
	inputFile.open(this->_inputFile.c_str());
	while (getline(inputFile, line)){
		if (line.empty() || line == "date | value")
			continue;
		if (!checkInput(line)) {
			std::cerr << "Error: Bad input: " << line << std::endl;
			continue;
		}
		if (!numError(line))
			continue;
		else{
			displayRate(line, this->_btc);
		}
	}
}
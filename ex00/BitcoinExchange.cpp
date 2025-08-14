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

bool BitcoinExchange::checkInput(const std::string& line) {
	// Check minimum length
	if (line.length() < 14) return false; // "YYYY-MM-DD | N" minimum
	// Check date format: YYYY-MM-DD
	if (line[4] != '-' || line[7] != '-') return false;
	// Check separator: " | "
	if (line.length() < 13 || line[10] != ' ' || line[11] != '|' || line[12] != ' ') return false;
	// Validate year (4 digits)
	for (int i = 0; i < 4; ++i) {
		if (!std::isdigit(line[i])) return false;
	}
	// Validate month (2 digits)
	for (int i = 5; i < 7; ++i) {
		if (!std::isdigit(line[i])) return false;
	}
	// Validate day (2 digits)
	for (int i = 8; i < 10; ++i) {
		if (!std::isdigit(line[i])) return false;
	}
	// Parse date components
	std::string year_str = line.substr(0, 4);
	std::string month_str = line.substr(5, 2);
	std::string day_str = line.substr(8, 2);

	int year = std::atoi(year_str.c_str());
	int month = std::atoi(month_str.c_str());
	int day = std::atoi(day_str.c_str());

	// Validate month range
	if (month < 1 || month > 12) return false;

	// Check days in month
	int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	if (is_leap) days_in_month[1] = 29;

	if (day < 1 || day > days_in_month[month - 1]) return false;

	// Validate number part after " | "
	std::string number_part = line.substr(13);
	if (number_part.empty()) return false;

	// Check for optional minus sign
	std::string::size_type start = 0;
	if (number_part[0] == '-') {
		if (number_part.length() == 1) return false; // Just a minus sign
		start = 1;
	}

	bool has_decimal = false;
	bool has_digits = false;

	for (std::string::size_type i = start; i < number_part.length(); ++i) {
		if (std::isdigit(number_part[i])) {
			has_digits = true;
		} else if (number_part[i] == '.' && !has_decimal) {
			has_decimal = true;
			// Decimal point must be followed by at least one digit
			if (i == number_part.length() - 1) return false;
		} else {
			return false; // Invalid character
		}
	}

	// Must have at least one digit
	if (!has_digits) return false;

	// If there's a decimal point, ensure digits after it
	if (has_decimal) {
		std::string::size_type decimal_pos = number_part.find('.');
		bool has_digits_after_decimal = false;
		for (std::string::size_type i = decimal_pos + 1; i < number_part.length(); ++i) {
			if (std::isdigit(number_part[i])) {
					has_digits_after_decimal = true;
					break;
			}
		}
		if (!has_digits_after_decimal) return false;
	}

	return true;
}

void BitcoinExchange::fillMap(std::map<std::string, float> &map, std::ifstream &infile){
	std::string ph;
	float s;
	std::string value;
	std::string date;

	if (!infile.is_open()) {
		std::cerr << "Error: Could not open file\n";
		return;
	}
	if (infile.eof())
		return;
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

void BitcoinExchange::exchange(std::ifstream &infile, const std::string &inputFile) {
	if (!infile.is_open()) {
		std::cerr << "Error: Could not open file " << inputFile << "\n";
		return;
	}

	this->_inputData.open(inputFile.c_str());
	if (!this->_inputData.is_open()) {
		std::cerr << "Error: Could not open input file " << inputFile << "\n";
		return;
	}

	std::map<std::string, float> bitcoinMap;

	fillMap(bitcoinMap, infile);

	std::string line;
	while (getline(this->_inputData, line)) {
		if (line.empty() || line == "date | value" || line == "data,exchange_rate")
			continue;
		if (!checkInput(line)) {
			std::cerr << "Error: Invalid input format: " << line << "\n";
			continue;
	}
	
		std::string date = line.substr(0, 10);
		std::string value = line.substr(13);

		if (bitcoinMap.find(date) == bitcoinMap.end()) {
			std::cerr << "Error: Date not found in dataset: " << date << "\n";
			continue;
		}

		float rate = bitcoinMap[date];
		float inputValue;
		try {
			inputValue = std::atof(value.c_str());
		} catch (const std::exception &e) {
			std::cerr << "Error: Invalid value for date " << date << ": " << value << "\n";
			continue;
		}

		if (!checkLimits(rate, inputValue)) {
			std::cerr << "Error: Value out of limits for date " << date << ": " << value << "\n";
			continue;
		}

		float result = rate * inputValue;
		std::cout << date << " => " << result << "\n";
	}
	this->_inputData.close();
	infile.close();
}
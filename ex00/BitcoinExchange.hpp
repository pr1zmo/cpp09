#ifndef Bitcoin_HPP
#define Bitcoin_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
// #include <regex>
#include <exception>
#include <map>
#include <limits>

class Bitcoin {
	private:
		std::map<std::string, float> _btc;
		std::string _inputFile;
		std::ifstream _data;
		Bitcoin();

	public:
		Bitcoin(std::string &argv);
		Bitcoin(const Bitcoin& other);
		Bitcoin& operator=(const Bitcoin& other);
		~Bitcoin();

		bool checkFiles(const std::string &argv);
		void fillMap(std::map<std::string, float> &map, std::ifstream &infile);
		void exchange();
		bool checkInput(const std::string& line);
		void displayRate(const std::string& line, std::map<std::string, float> &btc);
};

#endif
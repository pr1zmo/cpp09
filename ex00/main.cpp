#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

int main(int ac, char **av){
	BitcoinExchange btc;

	// if (ac != 2)
	// 	return (std::cout << "Wrong number of arguemnst\n", 1);
	std::ifstream bitcoinDB;
	std::ifstream inputTxt;
	bitcoinDB.open("test/data.csv");
	// inputTxt.open(std::string("test/") + av[1]);
	inputTxt.open("test/input.csv");
	// btc.checkFiles(bitcoinDB, inputTxt);
	// std::cout << inputTxt << std::endl;
	std::string l1;
	std::string l2;
	while (getline(bitcoinDB, l1))
	{
		// std::cout << l1 << std::endl;
		while (getline(inputTxt, l2))
		{
			// do something;
			if (l1.substr(0, 10).compare(l2.substr(0, 10)) == 0)
				std::cout << l1 << " --> " << l2 << std::endl;
		}
	}
}
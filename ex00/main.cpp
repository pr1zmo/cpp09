#include "BitcoinExchange.hpp"

int main(int ac, char **av){
	BitcoinExchange btc;

	if (ac != 2)
		return (std::cout << "Wrong number of arguemnst\n", 1);
	try{
		std::ifstream bitcoinDB("test/data.csv");
		std::string inputFile = av[1];
		btc.exchange(bitcoinDB, inputFile);
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}
}
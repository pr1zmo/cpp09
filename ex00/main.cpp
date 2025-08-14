#include "BitcoinExchange.hpp"
#include <iomanip>
#include <iostream>

int main(int ac, char **av){
	if (ac != 2)
		return (std::cout << "Wrong number of arguments\nUsage: ./btc ***.csv\n", 1);

	std::string s_av = av[1];
	Bitcoin btc(s_av);

	btc.exchange();
}
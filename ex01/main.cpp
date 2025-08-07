#include "RPN.hpp"

int main(int ac, char **av){
	if (ac != 2)
		return (std::cout << "Error\n", 1);
	RPN expr(av[1]);

	try{
		expr.loadExpression();
	}
	catch (std::exception &e){
		std::cout << "Caught exception: " << e.what();
	}
	return (0);
}
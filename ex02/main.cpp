#include "PmergeMe.hpp"

int main(int ac, const char **av){
	if (ac < 3) {
		std::cerr << "Usage: " << av[0] << " <numbers...>" << std::endl;
		return 1;
	}

	PmergeMe arr(av);

	arr.loadData();
	return (0);
}
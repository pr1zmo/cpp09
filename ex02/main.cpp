#include "PmergeMe.hpp"


// Example timing in main
int main(int argc, const char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <sequence of integers>" << std::endl;
		return 1;
	}
	PmergeMe vec(argv);

	vec.appMain();
	return 0;
}

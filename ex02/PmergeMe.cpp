#include "PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const char **av)
: _sequence(av){

}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	(void)other;
	return *this;
}

PmergeMe::~PmergeMe() {
}

void PmergeMe::loadData(){
	int c;
	for (int i = 1; this->_sequence[i]; i++){
		c = stof(this->_sequence[i], 0);
		this->_deqSeq.push_back(c);
		this->_vecSeq.push_back(c);
	}

	// Display the content of the vector
	std::cout << "Vector content: ";
	for (std::vector<int>::const_iterator it = _vecSeq.begin(); it != _vecSeq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// Display the content of the deque
	std::cout << "Deque content: ";
	for (std::deque<int>::const_iterator it = _deqSeq.begin(); it != _deqSeq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
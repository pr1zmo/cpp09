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

std::string PmergeMe::mergeSortDeq(std::deque<int> deque){
	//
	return "";
}

std::string PmergeMe::mergeSortVec(std::vector<int> vector){
	std::vector<int> res;

	// res = sort(vector);
	return "";
}

void PmergeMe::loadData(){
	int c;
	for (int i = 1; this->_sequence[i]; i++){
		c = std::atoi(this->_sequence[i]);
		this->_deqSeq.push_back(c);
		this->_vecSeq.push_back(c);
	}

	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = _vecSeq.begin(); it != _vecSeq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	mergeSortVec(this->_vecSeq);
	mergeSortDeq(this->_deqSeq);
	// Display the content of the vector
	std::cout << "After: ";
	for (std::vector<int>::const_iterator it = _vecSeq.begin(); it != _vecSeq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

/* 		// Display the content of the deque
	std::cout << "Deque content: ";
	for (std::deque<int>::const_iterator it = _deqSeq.begin(); it != _deqSeq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl; */
}
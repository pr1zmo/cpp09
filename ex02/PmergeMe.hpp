#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>

class PmergeMe {
	private:
		const char** _sequence;
		std::vector<int> _vecSeq;
		std::deque<int> _deqSeq;
		PmergeMe();
	public:
		PmergeMe(const char **av);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		void loadData();
		std::string mergeSortVec(std::vector<int> vec);
		std::string mergeSortDeq(std::deque<int> deq);
};

#endif
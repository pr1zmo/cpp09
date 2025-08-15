#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <sys/time.h>
#include <algorithm>
#include <iomanip>
#include <limits>

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
		void appMain();
		bool parseInput(const char** seq);
		void FordJohnson(std::vector<int>& vec);
		void FordJohnson(std::deque<int>& deq);
		void insertionSort(std::vector<int>& vec);
		void insertionSort(std::deque<int>& deq);
		void merge(std::deque<int> &L, std::deque<int> &R, std::deque<int> &deq);
		void merge(std::vector<int> &L, std::vector<int> &R, std::vector<int> &vec);
		size_t getTime();
		void showSeq(const std::string& type, double time);
};

// template <typename C>
// std::ostream& operator<<(std::ostream& o, C container);

#endif
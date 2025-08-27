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

void PmergeMe::insertionSort(std::vector<int> &vec) {
	for (int i = 0; i < (int)vec.size() - 1; i++){
		int z = i;
		int j = i + 1;
		while (i >= 0 && vec[i] > vec[j]){
			int temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			i--;
			j--;
		}
		i = z;
	}
}

void PmergeMe::insertionSort(std::deque<int> &deq){
	for (int i = 0; i < (int)deq.size() - 1; i++){
		int z = i;
		int j = i + 1;
		while (i >= 0 && deq[i] > deq[j]){
			int temp = deq[i];
			deq[i] = deq[j];
			deq[j] = temp;
			i--;
			j--;
		}
		i = z;
	}
}

void PmergeMe::merge(std::vector<int> &L, std::vector<int> &R, std::vector<int> &vec){
	size_t i = 0, j = 0, k = 0;
	while (i < R.size() && j < L.size()){
		if (R[i] <= L[j])
			vec[k++] = R[i++];
		else
			vec[k++] = L[j++];
	}
	while (i < R.size())
		vec[k++] = R[i++];
	while (j < L.size())
		vec[k++] = L[j++];
}

void PmergeMe::merge(std::deque<int> &L, std::deque<int> &R, std::deque<int> &deq){
	size_t i = 0, j = 0, k = 0;
	while (i < R.size() && j < L.size()){
		if (R[i] <= L[j])
			deq[k++] = R[i++];
		else
			deq[k++] = L[j++];
	}
	while (i < R.size())
		deq[k++] = R[i++];
	while (j < L.size())
		deq[k++] = L[j++];
}

void PmergeMe::FordJohnson(std::vector<int> &vec) {
	// if (vec.size() <= 1)
	// 	return;
	if (vec.size() <= 10) {
		insertionSort(vec);
		return;
	}
	int mid = vec.size() / 2;
	std::vector<int> leftVec(vec.begin(), vec.begin() + mid);
	std::vector<int> rightVec(vec.begin() + mid, vec.end());
	FordJohnson(leftVec);
	FordJohnson(rightVec);
	merge(leftVec, rightVec, vec);
}

void	PmergeMe::FordJohnson(std::deque<int> &deq) {
	if (deq.size() <= 10) {
		insertionSort(deq);
		return;
	}
	int mid = deq.size() / 2;
	std::deque<int> leftDeq(deq.begin(), deq.begin() + mid);
	std::deque<int> rightDeq(deq.begin() + mid, deq.end());
	FordJohnson(leftDeq);
	FordJohnson(rightDeq);
	merge(leftDeq, rightDeq, deq);
}

size_t PmergeMe::getTime(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long long)tv.tv_sec * 1000000 + tv.tv_usec;
}

bool isNum(const char* c){
	for (int i = 0; c[i]; i++)
		if (!isdigit(c[i])) return false;
	return true;
}

bool badNum(const char* c){
	long long int test = std::atoll(c);
	if (test < 0 || test > std::numeric_limits<int>::max())
		return true;
	return false;
}

bool PmergeMe::parseInput(const char** seq){
	for (int i = 1; seq[i]; i++){
		if (!isNum(seq[i])) {
			return false;
		}
		if (badNum(seq[i])) {
			return false;
		}
		int value = std::atoi(seq[i]);
		this->_vecSeq.push_back(value);
		this->_deqSeq.push_back(value);
	}
	return true;
}


void PmergeMe::showSeq(const std::string& type, double time) {
		std::cout << "Time to process a range of " << " elements with std::" << type
			<< " : " << std::fixed << std::setprecision(5) << time
			<< " us" << std::endl;
}

void beforeAfter(std::vector<int> &vec, size_t size){
	for (int i = 0; i < (int)vec.size(); i++){
		if (i == (int)size)
			break;
		std::cout << vec[i] << " ";
	}
	if (size < vec.size())
		std::cout << " [...]";
	std::cout << std::endl;
}

void PmergeMe::appMain(void){
	if (!parseInput(this->_sequence)){
		std::cerr << "Error\n";
		return ;
	}
	
	double vecTime;
	double deqTime;

	std::cout << "Before: ";
	beforeAfter(this->_vecSeq, 5);

	size_t time = getTime();
	FordJohnson(this->_vecSeq);
	vecTime = getTime() - time;

	std::cout << "After: ";
	beforeAfter(this->_vecSeq, 5);

	time = getTime();
	FordJohnson(this->_deqSeq);
	deqTime = getTime() - time;
	showSeq("vector", vecTime);
	showSeq("deque", deqTime);
}
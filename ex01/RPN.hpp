#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
	private:
		std::string _EXP;
		std::stack<char> _S_STK;
		std::stack<int> _N_STK;
		std::stack<char> _stack;
		RPN();
	public:
		RPN(const std::string &expression);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		class BadArgumentException : public std::exception{
			public:
				const char* what() const throw();
		};

		void loadExpression();
		void calcExp(std::stack<char> stack);

		// TESTING:
		template<typename T>
		void printStk(std::stack<T> stack);
};

#endif
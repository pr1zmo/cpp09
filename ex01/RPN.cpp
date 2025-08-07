#include "RPN.hpp"
#include <iostream>

RPN::RPN()
{
}

RPN::RPN(const std::string &expression)
	: _EXP(expression)
{
}

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
	}
	return *this;
}

RPN::~RPN() {
}

template<typename T>
void RPN::printStk(std::stack<T> stack){
	std::cout << "Printing the stack data:\n";

	while (!stack.empty()) {
		std::cout << stack.top() << std::endl;
		stack.pop();
	}
}

char getNextSym(const std::string &exp){
	static int c;

	while (exp[c]){
		c++;
		if (exp[c] == '+' || exp[c] == '-' || exp[c] == '/' || exp[c] == '*')
			return exp[c];
	}
	return '\0';
}

int op(char symbol, int ps, int result){
	switch(symbol){
		case '+':
			return result + ps;
		case '-':
			return result - ps;
		case '/':
			if (ps == 0){ throw std::runtime_error("Division by zero is not allowed.");} else{return result / ps;};
		case '*':
			return result * ps;
	}
	return 0;
}

void RPN::calcExp(std::stack<char> stack){
	int result = stack.top() - 48;
	stack.pop();
	
	while (!stack.empty()){
		if (isdigit(stack.top())){
			int firstArg = stack.top() - 48;
			stack.pop();
			result = op(stack.top(), firstArg, result);
		}
		stack.pop();
	}
	std::cout << result << std::endl;
}

int invalidSymbol(char c){
	if (c == '+' || c == '-' || c == '/' || c == '*' || isdigit(c))
		return 0;
	return 1;
}

const char* RPN::BadArgumentException::what() const throw() {
	return "Bad argument in RPN expression";
}

void RPN::loadExpression(){
	for (int i = this->_EXP.size() - 1; i >= 0; i--){
		if (this->_EXP.at(i) == ' ')
			continue;
		if (invalidSymbol(this->_EXP.at(i)))
			throw BadArgumentException();
		_stack.push(this->_EXP.at(i));
	}

	calcExp(this->_stack);
}
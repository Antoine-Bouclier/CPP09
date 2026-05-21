#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

bool	RPN::isOperator(int c)
{
	if (c == '/' || c == '*' || c == '-' || c == '+')
		return (true);
	return (false);
}

void	RPN::calculate(int c)
{
	int	b = stack.back();
	stack.pop_back();
	int	a = stack.back();
	stack.pop_back();

	if (c == '/')
	{
		if (b == 0)
			throw std::runtime_error("Error");
		stack.push_back(a / b);
	}
	else if (c == '*')
		stack.push_back(a * b);
	else if (c == '-')
		stack.push_back(a - b);
	else
		stack.push_back(a + b);
}

RPN::RPN(const std::string& str)
{
	for (iter it = str.begin(); it != str.end(); ++it)
	{
		if (*it == ' ')
			continue;

		if (isdigit(*it))
			stack.push_back(*it - 48);
		else if (isOperator(*it))
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error");
			calculate(*it);
		}
		else
			throw std::runtime_error("Error");
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error");
	else
		std::cout << stack.back() << std::endl;
}

RPN::RPN(const RPN& copy)
{
	*this = copy;
}

RPN	&RPN::operator=(const RPN& copy)
{
	if (this != &copy)
	{
		stack.assign(copy.stack.begin(), copy.stack.end());
	}
	return *this;
}

/* DEBUG */

void	RPN::printStack()
{
	for (std::list<int>::iterator it = stack.begin(); it != stack.end(); ++it)
	{
		std::cout << " [" << *it << "]";
	}
	std::cout << std::endl;
}
#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

bool	RPN::isOperator(int c)
{
	return (c == '/' || c == '*' || c == '-' || c == '+');
}

void	RPN::calculate(int c)
{
	int b = stack.back();
	stack.pop_back();
	int a = stack.back();
	stack.pop_back();

	long long res = 0;

	if (c == '+')
		res = static_cast<long long>(a) + b;
	else if (c == '-')
		res = static_cast<long long>(a) - b;
	else if (c == '*')
		res = static_cast<long long>(a) * b;
	else if (c == '/')
	{
		if (b == 0)
			throw std::runtime_error("Error");
		res = static_cast<long long>(a) / b;
	}

	if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min())
		throw std::runtime_error("Error");

	stack.push_back(static_cast<int>(res));
}

RPN::RPN(const std::string& str)
{
	for (iter it = str.begin(); it != str.end(); ++it)
	{
		if (*it == ' ' || *it == '\t')
			continue;

		iter next = it + 1;
		if (next != str.end() && *next != ' ' && *next != '\t')
			throw std::runtime_error("Error");

		if (std::isdigit(*it))
			stack.push_back(*it - '0');
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
	return (*this);
}
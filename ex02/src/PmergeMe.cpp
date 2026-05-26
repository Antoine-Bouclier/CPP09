#include "PmergeMe.hpp"

const size_t PmergeMe::jacobsthal[22] = {
	1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 
	2731, 5461, 10923, 21845, 43691, 87381, 174763, 
	349525, 699051, 1398101, 2796203
};

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	*this = copy;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe& copy)
{
	if (this != &copy)
		return (*this);
	return (*this);
}

void	PmergeMe::parseAndStore(char **arg, std::vector<int>& vec, std::deque<int>& deq)
{
	for (int i = 1; arg[i] != NULL; i++)
	{
		std::stringstream	ss(arg[i]);
		std::string			extra;
		int					num;

		if (!(ss >> num))
			throw ErrorException("All arguments must be integers.");
		if (ss >> extra)
			throw ErrorException("Invalid argument format.");
		if (num < 0)
			throw ErrorException("All arguments must be positive integers.");
		deq.push_back(num);
		vec.push_back(num);
	}
}

void	PmergeMe::print(std::string str, const std::vector<int> container)
{
	std::cout << str;
	for (size_t i = 0; i < container.size(); i++)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;
}
#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::~PmergeMe()
{

}

PmergeMe::PmergeMe(char **argv)
{
	parseAndStore(argv);
	print("Before: ");
	sortPairs(vec, 1);
	print("After: ");
}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	(void)copy;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe& copy)
{
	(void)copy;
	return (*this);
}

void	PmergeMe::sortPairs(std::vector<int>& container, size_t blockSize)
{
	size_t totalElements = container.size();

	if (totalElements < 2 * blockSize)
		return;

	for (size_t i = 0; i + 2 * blockSize <= totalElements; i += 2 * blockSize)
	{
		size_t firstMaxIdx = i + blockSize - 1;
		size_t secondMaxIdx = i + 2 * blockSize - 1;

		if (container[firstMaxIdx] > container[secondMaxIdx])
		{
			std::swap_ranges(
				container.begin() + i, 
				container.begin() + i + blockSize, 
				container.begin() + i + blockSize
			);
		}
		/* DEBUG */
		printBetween(i, i + 2 * blockSize);
	}
	std::cout << std::endl;
	sortPairs(container, blockSize * 2);
	pushAndInsert(container, blockSize);
}

void PmergeMe::pushAndInsert(std::vector<int>& container, size_t blockSize)
{
	std::vector<int>	pend;
	std::vector<int>	main;

	std::vector<int>::iterator	it = container.begin();

	for (; static_cast<size_t>(std::distance(it, container.end())) >= blockSize * 2; it += 2 * blockSize)
	{
		pend.insert(pend.end(), it, it + blockSize);
		main.insert(main.end(), it + blockSize, it + blockSize * 2);
	}

	if (static_cast<size_t>(std::distance(it, container.end())) >= blockSize)
		pend.insert(pend.end(), it, it + blockSize);

	main.insert(main.begin(), pend.begin(), pend.begin() + blockSize);

	
}

void	PmergeMe::parseAndStore(char **arg)
{
	for (int i = 1; arg[i] != '\0'; i++)
	{
		std::stringstream	ss(arg[i]);
		int					num;
		if (!(ss >> num))
			throw ErrorException("All arguments must be positive integer.");
		std::string extra;
		if (ss >> extra)
			throw ErrorException("All arguments must be positive integer.");
		if (num < 1 || num > std::numeric_limits<int>::max())
			throw ErrorException("All arguments must be positive integer.");
		deque.push_back(num);
		vec.push_back(num);
	}
}

void	PmergeMe::print(std::string str)
{
	std::cout << str;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void	PmergeMe::printBetween(size_t first, size_t last)
{
	std::cout << '[';
	bool	space = false;
	for (;first < last; first++)
	{
		if (space)
			std::cout << ' ';
		std::cout << vec[first];
		space = true;
	}
	std::cout << "] ";
}
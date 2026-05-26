#include "PmergeMe.hpp"

#include <ctime>

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);

	std::vector<int> myVector;
	std::deque<int>  myDeque;

	try
	{
		PmergeMe::parseAndStore(av, myVector, myDeque);
		
		PmergeMe::print("Before: ", myVector);

		std::clock_t startVector = std::clock();
		PmergeMe::sortPairs(myVector, 1);
		std::clock_t endVector = std::clock();

		std::clock_t startDeque = std::clock();
		PmergeMe::sortPairs(myDeque, 1);
		std::clock_t endDeque = std::clock();

		PmergeMe::print("After:  ", myVector);

		double durationVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
		double durationDeque  = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;

		std::cout << "Time to process a range of " << myVector.size() 
				  << " elements with std::vector : " << durationVector << " us" << std::endl;

		std::cout << "Time to process a range of " << myDeque.size() 
				  << " elements with std::deque  : " << durationDeque << " us" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
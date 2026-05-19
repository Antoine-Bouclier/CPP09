#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include <iostream>
#include <exception>
#include <sstream>
#include <limits>
#include <algorithm>

class PmergeMe
{
	private:
		std::deque<int>		deque;
		std::vector<int>	vec;

		size_t	jacobsthal[30] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203};

		struct BlockComparator {
			bool operator()(const std::vector<int>& a, const std::vector<int>& b) const
			{
				return a.back() < b.back();
			}
		};
		
		PmergeMe();
		void	parseAndStore(char **arg);
		void	sortPairs(std::vector<int>& container, size_t blockSize);
		void	print(std::string str);
		void	printBetween(size_t first, size_t last);
		void	pushAndInsert(std::vector<int>& container, size_t blockSize);

	public:
		~PmergeMe();
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe& copy);
		PmergeMe	&operator=(const PmergeMe& copy);

	class ErrorException : public std::exception
		{
			private:
				std::string	_message;
			public:
				ErrorException(std::string const& message) : _message("ERROR: " + message) {}
				virtual const char* what() const throw() { return _message.c_str(); }
				virtual ~ErrorException() throw() {}
		};
};

#endif
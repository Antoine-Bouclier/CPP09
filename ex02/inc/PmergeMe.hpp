#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include <iostream>
#include <exception>
#include <sstream>
#include <limits>
#include <algorithm>

typedef std::vector<int>::iterator iter;

class PmergeMe
{
	private:
		std::deque<int>		deque;
		std::vector<int>	vec;

		static const size_t	jacobsthal[30];
		
		PmergeMe();
		void	parseAndStore(char **arg);
		void	sortPairs(std::vector<int>& container, size_t blockSize);
		void	print(std::string str);
		void	printBetween(size_t first, size_t last);
		void	pushAndInsert(std::vector<int>& container, size_t blockSize);
		iter	customUpperBound(iter first, iter last, const int value, size_t blockSize);

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
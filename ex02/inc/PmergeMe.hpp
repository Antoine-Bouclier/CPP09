#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include <iostream>
#include <exception>
#include <sstream>
#include <limits>

class PmergeMe
{
	private:
		std::deque<int>	deque;
		std::vector<int>	vec;
		
		PmergeMe();
		void	parseAndStore(char **arg);
		void	sortPairs(std::vector<int>& container, size_t blockSize);
		void	print(std::string str);
		void	printBetween(size_t first, size_t last);
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
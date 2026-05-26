#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include <iostream>
#include <exception>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iterator>

class PmergeMe
{
	private:
		/* -- Private constructors & destructor -- */
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe	&operator=(const PmergeMe& copy);
		~PmergeMe();

		template <typename Iterator>
		static Iterator	customUpperBound(Iterator first, Iterator last, const int value, size_t blockSize)
		{
			size_t	count = std::distance(first, last) / blockSize;
			
			while (count != 0)
			{
				size_t		step = count / 2;
				Iterator	mid = first + step * blockSize;

				if (value < *(mid + (blockSize - 1)))
					count = step;
				else
				{
					first = mid + blockSize;
					count  = count - step - 1;
				}
			}
			return (first);
		}

		static const size_t	jacobsthal[22];
	public:

		static void	parseAndStore(char **arg, std::vector<int>& vec, std::deque<int>& deq);
		static void	print(std::string str, const std::vector<int> container);

		template <typename Container>
		static void	sortPairs(Container& container, size_t blockSize)
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
			}
			sortPairs(container, blockSize * 2);
			pushAndInsert(container, blockSize);
		}

		template <typename Container>
		static void	pushAndInsert(Container& container, size_t blockSize)
		{
			typedef typename Container::iterator iter;

			Container	pend;
			Container	main;
			Container	orphan;

			iter	it = container.begin();

			for (; static_cast<size_t>(std::distance(it, container.end())) >= blockSize * 2; it += 2 * blockSize)
			{
				pend.insert(pend.end(), it, it + blockSize);
				main.insert(main.end(), it + blockSize, it + blockSize * 2);
			}

			if (static_cast<size_t>(std::distance(it, container.end())) >= blockSize)
			{
				pend.insert(pend.end(), it, it + blockSize);
				it += blockSize;
			}

			orphan.insert(orphan.begin(), it, container.end());

			main.insert(main.begin(), pend.begin(), pend.begin() + blockSize);

			size_t	target;
			size_t	last;
			size_t	nb_blocks = pend.size() / blockSize;

			size_t	insertion_count = 1;
			for (int i = 1; i < 22 && jacobsthal[i - 1] < nb_blocks; i++)
			{
				if (jacobsthal[i] > nb_blocks)
					target = nb_blocks;
				else
					target = jacobsthal[i];
				last = jacobsthal[i - 1];
				
				for (size_t j = target; j > last; j--)
				{
					size_t	bound_end = j + insertion_count;
					iter	begin = pend.begin() + (j - 1) * blockSize;
					iter	end = begin + blockSize;

					size_t	offset = bound_end * blockSize;
					size_t	offsetSecure = (offset > main.size()) ? main.size() : offset;

					iter	upper = customUpperBound(main.begin(), main.begin() + offsetSecure, *(end - 1), blockSize);

					main.insert(upper, begin, end);
					insertion_count++;
				}
			}
			container.swap(main);
			container.insert(container.end(), orphan.begin(), orphan.end());
		}

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
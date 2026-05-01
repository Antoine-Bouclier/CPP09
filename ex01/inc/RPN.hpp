#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <list>
#include <exception>

typedef typename std::string::const_iterator iter;

class RPN
{
	private:
		std::list<int>	stack;

		RPN();
		bool	isOperator(int c);
		void		calculate(int c);

		/* DEBUG */
		void	printStack();
	public:
		~RPN();
		RPN(const std::string& str);
		RPN(const RPN& copy);
		RPN	&operator=(const RPN& copy);
};

#endif
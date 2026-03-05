#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <exception>
#include <fstream>
#include <sstream>

#include <sys/stat.h>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_data;

		BitcoinExchange();
		void	initData();
		bool	isDateValid(const std::string& date_str);
		bool	isValueValid(const std::string& val_str);
		void	processInput(const char* path);
	public:
		BitcoinExchange(const std::string& file);
		BitcoinExchange(const BitcoinExchange& copy);
		BitcoinExchange	&operator=(const BitcoinExchange& copy);
		~BitcoinExchange();
};


#endif
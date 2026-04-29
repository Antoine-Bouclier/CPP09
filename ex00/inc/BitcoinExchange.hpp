#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	data;

		BitcoinExchange();
		void			parseData();
		bool			isValidDate(const std::string date_str);
		bool			isValidValue(const std::string value_str);
		int	stoi(const std::string str);
		bool			isValidYear(const std::string year);
		bool			isValidMonth(const std::string month);
		bool			isValidDay(const std::string year, const std::string month, const std::string day);
	public:
		~BitcoinExchange();
		BitcoinExchange(const std::string& file);
		BitcoinExchange(const BitcoinExchange& copy);
		BitcoinExchange	&operator=(const BitcoinExchange& copy);

		class ErrorException : public std::exception
		{
			private:
				std::string	_message;
			public:
				ErrorException(std::string const& message) : _message("ERROR: " + message) {}
				ErrorException(std::string const& message, unsigned int line) 
				{
					std::stringstream ss;
					ss << "ERROR [line " << line << "]: " << message;
					_message = ss.str();
				}
				virtual const char* what() const throw() { return _message.c_str(); }
				virtual ~ErrorException() throw() {}
		};
};

#endif
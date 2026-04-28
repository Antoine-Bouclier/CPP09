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
		void			stoi(const std::string value);
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
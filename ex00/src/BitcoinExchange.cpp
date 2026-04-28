#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}
BitcoinExchange::~BitcoinExchange()
{

}
BitcoinExchange::BitcoinExchange(const std::string& file)
{
	parseData();
	(void)file;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{
	(void)copy;
}
BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange& copy)
{
	(void)copy;
	return (*this);
}

void	BitcoinExchange::parseData()
{
	std::ifstream	file("data/data.csv");
	std::string		line;

	if (!file.is_open())
		throw ErrorException("Could not open data file");

	if (!std::getline(file, line))
		throw	ErrorException("empty data.csv file.");

	unsigned int	count = 2;
	while (std::getline (file, line))
	{
		size_t			found = line.find(',');
		if (found != std::string::npos)
		{
			std::string	date = line.substr(0, found - 1);
			std::string	value = line.substr(found + 1);
			
			if (!isValidDate(date))
				throw ErrorException("Invalid date in data.csv: Requires: [YYYY-MM-DD] (Range: 2009-01-02 | 9999-12-31)", count);
			else if (!isValidValue(value))
				throw ErrorException("Invalid value in data.csv: Requires a float or positive integer", count);
			else
			{
				std::cout << value << std::endl;
				std::stringstream ss(value);
				double val;
				if (!(ss >> val))
					throw ErrorException("Value cannot be convert.", count);
				data.insert(std::pair<std::string, double>(date, val));
			}
		}
		count++;
	}
}

bool	BitcoinExchange::isValidDate(const std::string date_str)
{
	size_t	first = date_str.find('-');
	size_t	last = date_str.rfind('-');

	if (first != std::string::npos && last != std::string::npos)
	{
		std::stringstream ss(date_str.substr(0, first - 1));
		unsigned int	num;
		if (!(ss >> num))
			return (false);
		if (num < 0 || num > 9999)
			return (false);

		
		std::string	year = date_str.substr(0, first - 1);
		std::string	month = date_str.substr(first + 1, last - 1);
		std::string	day = date_str.substr(last + 1);
	}
	return (false);
}

void	BitcoinExchange::stoi(const std::string value)
{
	
}

bool	BitcoinExchange::isValidValue(const std::string value_str)
{
	(void)value_str;
	return (true);
}

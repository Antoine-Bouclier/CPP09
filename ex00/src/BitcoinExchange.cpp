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
			std::string	date = line.substr(0, found);
			std::string	value = line.substr(found + 1);
			
			if (!isValidDate(date))
				throw ErrorException("Invalid date in data.csv: Requires: [YYYY-MM-DD] (Range: 2009-01-02 | 9999-12-31)", count);
			else if (!isValidValue(value))
				throw ErrorException("Invalid value in data.csv: Requires a float or positive integer", count);
			else
			{
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
		std::string	year = date_str.substr(0, first);
		std::string	month = date_str.substr(first + 1, last - first - 1);
		std::string	day = date_str.substr(last + 1);
		if (!isValidYear(year) || !isValidMonth(month) || !isValidDay(year, month, day))
			return (false);
	}
	return (true);
}

bool	BitcoinExchange::isValidValue(const std::string value_str)
{
	(void)value_str;
	return (true);
}

int			BitcoinExchange::stoi(const std::string str)
{
	std::stringstream ss(str);
	unsigned int	num;
	if (!(ss >> num))
		return (-1);
	return (num);
}

bool			BitcoinExchange::isValidYear(const std::string year)
{
	int	num = stoi(year);
	if (!num || num < 0 || num > 9999)
		return (false);
	return (true);
}

bool			BitcoinExchange::isValidMonth(const std::string month)
{
	int	num = stoi(month);
	if (num < 0 || num > 12)
		return (false);
	return (true);
}

bool			BitcoinExchange::isValidDay(const std::string year, const std::string month, const std::string day)
{
	int	y = stoi(year);
	int	m = stoi(month);
	int	d = stoi(day);
	if (d < 1 || d > 31)
		return (false);
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
		return (false);
	if (m == 2)
	{
		bool isLeap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
		if (isLeap && d > 29)
			return (false);
		else if (!isLeap && d > 28)
			return (false);
	}
	return (true);
}

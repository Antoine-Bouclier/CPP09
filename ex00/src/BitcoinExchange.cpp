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
	processInput(file);
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
		else
			throw	ErrorException("Invalid format", count);
		count++;
	}
}

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
		throw ErrorException("Could not open input file");

	if (!std::getline(file, line))
		throw	ErrorException("empty input file.");

	while (std::getline(file, line))
	{
		size_t	found = line.find('|');
		if (found != std::string::npos)
		{
			std::string	date = line.substr(0, found - 1);
			std::string	value = line.substr(found + 2);
			std::stringstream ss(value);
			double	val;
			std::string extra;
			
			if (!isValidDate(date))
				std::cout << "Error: bad input => " << line << std::endl;
			else if (!(ss >> val))
				std::cout << "Error: bad input => " << line << std::endl;
			else if (ss >> extra)
				std::cout << "Error: bad input => " << line << std::endl;
			else if (val < 0 || val > 1000)
				std::cout << "Error: number must be between 0 and 1000" << std::endl;
			else
			{
				std::map<std::string, double>::iterator it;
				it = data.lower_bound(date);
				if (it != data.end() && it->first == date)
				{
					std::cout << date << " => " << val << " = " << (val * it->second) << std::endl;
				}
				else
				{
					if (it == data.begin())
					{
						std::cout << "Error: no exchange rate found for this date (too old) => " << date << std::endl;
					}
					else
					{
						--it;
						std::cout << date << " => " << val << " = " << (val * it->second) << std::endl;
					}
				}
				it = data.lower_bound(date);
			}
		}
		else
			std::cout << "Error: bad input => " << line << std::endl;
	}
}

bool	BitcoinExchange::isValidDate(const std::string date_str)
{
	size_t	first = date_str.find('-');
	size_t	last = date_str.rfind('-');

	if (first == std::string::npos || last == std::string::npos || first == last)
		return (false);
	std::string	year = date_str.substr(0, first);
	std::string	month = date_str.substr(first + 1, last - first - 1);
	std::string	day = date_str.substr(last + 1);
	if (year.size() != 4 || month.size() != 2 || day.size() != 2)
		return (false);
	if (!isValidYear(year) || !isValidMonth(month) || !isValidDay(year, month, day))
		return (false);
	return (true);
}

bool	BitcoinExchange::isValidValue(const std::string value_str)
{
	std::stringstream ss(value_str);
	double	val;
	if (!(ss >> val))
		return (false);
	else if (val < 0)
		return (false);

	std::string extra;
	if (ss >> extra)
		return (false);
	return (true);
}

int			BitcoinExchange::stoi(const std::string str)
{
	std::stringstream ss(str);
	int	num;
	if (!(ss >> num))
		return (-1);
	std::string extra;
	if (ss >> extra)
		return (-1);
	return (num);
}

bool			BitcoinExchange::isValidYear(const std::string year)
{
	int	num = stoi(year);
	if (num < 0 || num > 9999)
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

std::map<std::string, double>::iterator			BitcoinExchange::search(const std::string date)
{
	std::map<std::string, double>::iterator it;

	it = data.lower_bound(date);

	return (it);
}

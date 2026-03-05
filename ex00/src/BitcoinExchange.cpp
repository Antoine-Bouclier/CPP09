#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const std::string& file)
{

}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{

}
BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange& copy)
{

}

BitcoinExchange::~BitcoinExchange()
{

}

void	BitcoinExchange::initData()
{
	std::ifstream	file("../data/data.csv");

	if (!file.is_open())
		throw	std::invalid_argument("Cannot open data file");
		
	std::string	line;
	if (!std::getline(file, line))
		return ;

	while (std::getline(file, line))
	{
		size_t	found = line.find(',');
		if (found != std::string::npos)
		{
			std::string	date = line.substr(0, found - 1);
			std::string	value = line.substr(found + 2);

			if (!isDateValid(date))
				std::cout << "Invalid date Requires: [YYYY-MM-DD]" << std::endl;
			else if (!isValueValid(value))
				std::cout << "Invalid value : Requires a float or positive integer between 0 and 1000" << std::endl;
				
		}
	}
}

bool	isValidYear(unsigned int year)
{
	if (year < 2009 || year > 9999)
		return (false);
	return (true);
}

bool	isValidMonth(unsigned int month)
{
	if (month < 1 || month > 12)
		return (false);
	return (true);
}

bool	isValidDay(unsigned int day, unsigned int month)
{
	if (day < 1 || day > 31)
		return (false);
	else if (month % 2 == 1)
}

bool	BitcoinExchange::isDateValid(const std::string& date_str)
{
	if (date_str.size() != 10 || date_str[4] != '-' || date_str[7] != '-')
		return (false);

	for (int i = 0; i < date_str.size() - 1; i++)
	{
		if (!isdigit(date_str[i]))
			return (false);
		if (i == 3 || i == 6)
			i++;
	}

	unsigned int	year = std::atoi(date_str.substr(0, 4).c_str());
	if (year < 2009 || year > 9999)
		throw std::invalid_argument("year not valid");
	unsigned int	month = std::atoi(date_str.substr(5, 2).c_str());
	if (month < 1 || month > 12)
		throw std::invalid_argument("month must be between 01 and 12.");
	unsigned int	day = std::atoi(date_str.substr(8, 2).c_str());
	if (day < 1 || day > 31)

	return (true);
}

bool	BitcoinExchange::isValueValid(const std::string& val_str)
{

	return (true);
}


void	BitcoinExchange::processInput(const char* path)
{
	struct stat buf;

	if (stat(path, &buf) == -1)
		throw	std::invalid_argument(std::string(path) + ": No such file or directory");
	if (S_ISDIR(buf.st_mode)) 
		throw	std::invalid_argument(std::string(path) + " is a Directory");
	else if (S_ISREG(buf.st_mode))
	{
		std::ifstream	file(path);
		if (!file.is_open())
			throw	std::invalid_argument("Cannot open config file");
		
		std::string	line;
		if (!std::getline(file, line))
			return ;

		unsigned int	current_line = 1;
		while (std::getline(file, line))
		{
			size_t	found = line.find('|');
			if (found != std::string::npos)
			{
				std::string	date = line.substr(0, found - 1);
				std::string	value = line.substr(found + 2);

				if (!isDateValid(date))
					std::cout << "Invalid date (" << current_line << ") Requires: [YYYY-MM-DD]" << std::endl;
				else if (!isValueValid(value))
					std::cout << "Invalid value (" << current_line << ") : Requires a float or positive integer between 0 and 1000" << std::endl;
				
			}
			// 4. Faire le calcul avec la map
			// 5. Afficher le résultat ou l'erreur
			current_line++;
		}
	}
	else
		throw	std::invalid_argument(std::string(path) + " is unknown");
}
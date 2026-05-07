#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
		std::cout << "No argument provided. Need 1 at least." << std::endl;
	else
	{
		try
		{
			PmergeMe	sort(argv);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}
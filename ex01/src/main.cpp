#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		try
		{
			RPN	rpn(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}
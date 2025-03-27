#include "CarController.h"
#include <iostream>

int main()
{
	CarController UI(std::cin, std::cout);
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			UI.HandleUserInput(line);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}

	return EXIT_SUCCESS;
}
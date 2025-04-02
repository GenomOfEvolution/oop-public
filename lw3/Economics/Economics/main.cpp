#include "CSimulation.h"
#include <optional>

bool ParseInt(const std::string& str, int& result) 
{
    try 
    {
        size_t pos = 0;
        result = std::stoi(str, &pos);

        return pos == str.size();
    }
    catch (...)
    {
        return false;
    }
}

struct Args
{
	int iterations = 0;
	bool isStdin = false;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc == 2)
	{
		int iterations;
		if (!ParseInt(argv[1], iterations))
		{
			std::cout << "Invalid number of iteratins\n";
			return std::nullopt;
		}

		return Args{ .iterations = iterations };
	}

	if (argc == 1)
	{
		return Args{ .isStdin = true };
	}

	std::cout << "Usage: Economics.exe <iterations> \n"
		<< "OR\n"
		<< "Economics.exe [enter iterations via stdin] \n";

	return std::nullopt;
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	int iterations;

	if (args->isStdin)
	{
		std::cout << "Enter iterations number: ";
		std::string line;
		std::getline(std::cin, line);

		if (!ParseInt(line, iterations))
		{
			std::cout << "Invalid number of iteratins\n";
			return EXIT_FAILURE;
		}
	}
	else
	{
		iterations = args->iterations;
	}

	CSimulation economics;
	economics.RunSimulation(iterations);

	return EXIT_SUCCESS;
}
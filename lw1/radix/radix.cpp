#include "radix.h"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Wrong parametrs! \n" <<
			"Use instead: radix.exe <source notation> <destination notation> <value>";
		return std::nullopt;
	}

	Args result;
	result.sourseNotation = std::stoi(argv[1]);
	result.destNotation = std::stoi(argv[2]);
	result.valueString = argv[3];

	return result;
}

std::optional<int> TransformCharToInt(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
	{
		return ch - DEF_ZERO_CHAR;
	}
	
	if ((ch >= 'A') && (ch <= 'Z'))
	{
		return *std::find(ALPHABET.begin(), ALPHABET.end(), ch) - DEF_A_CHAR + FIRST_CHAR_WEIGHT;
	}

	return std::nullopt;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{	
	if ((radix > 36) || (radix < 2))
	{
		wasError = true;
		std::cout << "Radix should be between 2 and 36!\n";
		return 0;
	}

	bool isNegative = false;
	std::string tempStr = str;

	if (str[0] == MINUS_CHAR)
	{
		isNegative = true;
		tempStr.erase(0, 1);
	}

	for (auto i : tempStr)
	{
		std::optional<int> charAsInt = 0;
		charAsInt = TransformCharToInt(i);

		if ((charAsInt == std::nullopt) || (*charAsInt > radix) || (*charAsInt < 0) )
		{
			wasError = true;
			std::cout << i << " is out of radix " << radix << "\n";
			return 0;
		}
	}

	double result = 0;

	for (auto i : tempStr)
	{
		std::optional<int> charNumber = TransformCharToInt(i);

		if (result > (INT_MAX - (*charNumber)) / radix)
		{
			std::cout << "Too big number in dec system!\n";
			wasError = true;
			return 0;
		}
		result = result * radix + (*charNumber);
	}

	if (isNegative)
	{
		result *= -1;
	}
	wasError = false;

	return int(result);
}

std::string ConvertNumberToNotation(int num)
{
	return ((num >= 0) && (num <= 9)) ? std::to_string(num) : std::string { ALPHABET[num - FIRST_CHAR_WEIGHT] };
}

std::string IntToString(int n, int radix, bool& wasError)
{
	if ((radix > 36) || (radix < 2))
	{
		wasError = true;
		std::cout << "Radix should be between 2 and 36!\n";
		return std::string {};
	}

	bool isNegative = false;
	if (n < 0)
	{
		isNegative = true;
		n *= -1;
	}

	std::string result;
	int remainder = 0;
	while (n >= radix)
	{
		remainder = n % radix;
		result.insert(0, ConvertNumberToNotation(remainder));
		n /= radix;
	}

	remainder = n % radix;
	result.insert(0, ConvertNumberToNotation(remainder));

	if (isNegative)
	{
		result.insert(0, std::string {MINUS_CHAR});
	}

	wasError = false;

	return result;
}

int main(int argc, char* argv[])
{
	std::optional<Args> tempArgs;
	tempArgs = ParseArgs(argc, argv);

	if (tempArgs == std::nullopt)
	{
		return EXIT_FAILURE;
	}

	Args args = *tempArgs;

	bool wasError = false;
	int inDecNumber = StringToInt(args.valueString, args.sourseNotation, wasError);

	if (wasError)
	{
		return EXIT_FAILURE;
	}

	std::string result = IntToString(inDecNumber, args.destNotation, wasError);
	
	if (wasError)
	{
		return EXIT_FAILURE;
	}
	std::cout << result << "\n";

	return EXIT_SUCCESS;
}
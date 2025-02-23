#include "radix.h"

// Тесты на INTMAX+1, INTMIN-1, проверка на переполнение
// Переписать на исключения

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

// убрать optional, выбрасывать исключение
// избавиться от ALPHABET и find
int TransformCharToInt(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
	{
		return ch - DEF_ZERO_CHAR;
	}
	
	if ((ch >= 'A') && (ch <= 'Z'))
	{
		return *std::find(ALPHABET.begin(), ALPHABET.end(), ch) - DEF_A_CHAR + FIRST_CHAR_WEIGHT;
	}

	throw std::runtime_error("Unable to transform char: " + ch);
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

	// не создавать строку а с 1 символа, если минус
	isNegative = (str[0] == MINUS_CHAR);

	// объеденить в 1 цикл
	for (int i = (isNegative ? 1 : 0); i < str.length(); i++)
	{
		int charAsInt = TransformCharToInt(str[i]);

		if ((charAsInt > radix) || (charAsInt < 0))
		{
			wasError = true;
			std::cout << i << " is out of radix " << radix << "\n";
			return 0;
		}
	}

	// сделать в int
	int result = 0;

	for (auto i : tempStr)
	{
		int charNumber = TransformCharToInt(i);

		if (result > (INT_MAX - (charNumber)) / radix)
		{
			std::cout << "Too big number in dec system!\n";
			wasError = true;
			return 0;
		}
		result = result * radix + (charNumber);
	}

	if (isNegative)
	{
		result *= -1;
	}
	wasError = false;

	return result;
}

void CheckRadix(int radix)
{
	if ((radix > 36) || (radix < 2))
	{
		throw std::runtime_error("Radix should be between 2 and 36!\n");
	}
}

std::string ConvertNumberToNotation(int num)
{
	return ((num >= 0) && (num <= 9)) ? std::to_string(num) : std::string { ALPHABET[num - FIRST_CHAR_WEIGHT] };
}

std::string IntToString(int n, int radix)
{
	CheckRadix(radix);

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

	return result;
}

int main(int argc, char* argv[])
{
	// сразу дать значение
	std::optional<Args> tempArgs;
	tempArgs = ParseArgs(argc, argv);

	// .hasValue
	if (tempArgs == std::nullopt)
	{
		return EXIT_FAILURE;
	}

	// разыменовать и передать
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
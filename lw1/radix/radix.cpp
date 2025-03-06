// Тесты на INTMAX+1, INTMIN-1, проверка на переполнение
// Переписать на исключения

#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>

const int FIRST_CHAR_WEIGHT = 10;
const int DEF_ZERO_CHAR = 48;
const int DEF_A_CHAR = 65;
const char MINUS_CHAR = '-';

struct Args
{
    int sourceNotation = 10;
    int destNotation = 10;
    std::string valueString;
};

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        throw std::runtime_error("Wrong parameters! Use instead: radix.exe <source notation> <destination notation> <value>");
    }

    Args result;
    result.sourceNotation = std::stoi(argv[1]);
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
        return ch - DEF_A_CHAR + FIRST_CHAR_WEIGHT;
    }

    throw std::runtime_error("Unable to transform char: " + std::string(1, ch));
}

void CheckRadix(int radix)
{
    if ((radix > 36) || (radix < 2))
    {
        throw std::runtime_error("Radix should be between 2 and 36!");
    }
}

// Убрать wasError, выбрасывать исключение
int StringToInt(const std::string& str, int radix)
{
    CheckRadix(radix);

    bool isNegative = (str[0] == MINUS_CHAR);
    int result = 0;

    for (size_t i = (isNegative ? 1 : 0); i < str.length(); i++)
    {
        int charAsInt = TransformCharToInt(str[i]);

        if ((charAsInt >= radix) || (charAsInt < 0))
        {
            throw std::runtime_error("Character is out of radix " + std::to_string(radix));
        }

        if (result > (INT_MAX - charAsInt) / radix)
        {
            throw std::runtime_error("Too big number in decimal system!");
        }

        result = result * radix + charAsInt;
    }

    return isNegative ? -result : result;
}

char ConvertNumberToChar(int num)
{
    if (num >= 0 && num <= 9)
    {
        return static_cast<char>(DEF_ZERO_CHAR + num);
    }
    else if (num >= 10 && num <= 35)
    {
        return static_cast<char>(DEF_A_CHAR + (num - FIRST_CHAR_WEIGHT));
    }
    throw std::runtime_error("Number is out of range for conversion to char: " + std::to_string(num));
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
        result.insert(0, 1, ConvertNumberToChar(remainder));
        n /= radix;
    }

    remainder = n % radix;
    result.insert(0, 1, ConvertNumberToChar(remainder));

    if (isNegative)
    {
        result.insert(0, 1, MINUS_CHAR);
    }

    return result;
}


// Проверить тест с INT_MIN
int main(int argc, char* argv[])
{
    try
    {
        Args args = ParseArgs(argc, argv);

        int inDecNumber = StringToInt(args.valueString, args.sourceNotation);
        std::string result = IntToString(inDecNumber, args.destNotation);

        std::cout << result << "\n";
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

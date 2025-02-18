// Тесты на неправильное кол-во парам. done
// Можно ли открыть файлы
// 16 test - error


#include <iostream>
#include <fstream>
#include <string>
#include <optional>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::string searchString;
    std::string replaceString;
    bool useStdin = false;
};

std::string ReplaceString(const std::string& stringToReplace, const std::string& oldValue, const std::string& newValue)
{
    if (oldValue.empty())
    {
        return stringToReplace;
    }

    std::string result;

    size_t startPos = 0;
    size_t endPos = 0;

    while ((endPos = stringToReplace.find(oldValue, startPos)) != std::string::npos)
    {
        result.append(stringToReplace, startPos, endPos - startPos);
        result += newValue;
        startPos = endPos + oldValue.length();
    }

    result.append(stringToReplace, startPos, std::string::npos);

    return result;
}


// Переименовать done
// ReplaceString - заменить на потоки done
bool ReplaceStrings(const Args& args)
{
    std::ifstream fileInputStream;
    std::ofstream fileOutputStream;

    if (!args.useStdin)
    {
        fileInputStream.open(args.inputFileName);
        if (!fileInputStream)
        {
            std::cout << "ERROR\n";
            return false;
        }

        fileOutputStream.open(args.outputFileName);
        if (!fileOutputStream)
        {
            std::cout << "ERROR" << std::endl;
            return false;
        }
    }

    std::istream& inputStream = args.useStdin ? std::cin : fileInputStream;
    std::ostream& outputStream = args.useStdin ? std::cout : fileOutputStream;

    std::string line;
    while (std::getline(inputStream, line))
    {
        outputStream << ReplaceString(line, args.searchString, args.replaceString) << '\n';
    }

    return true;
}

void PrintHelp()
{
    std::cout << "Usage: StringReplace.exe [options] <input file> <output file> <search string> <replace string>\n"
        << "Options:\n"
        << "  -h  Show this help message\n"
        << "If no arguments are provided, input is read from stdin and output is printed to console.\n";
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args result;

    if (argc == 1)
    {
        result.useStdin = true;

        if (!std::getline(std::cin, result.searchString))
        {
            std::cout << "ERROR" << std::endl;
            return std::nullopt;
        }

        if (!std::getline(std::cin, result.replaceString)) 
        {
            std::cout << "ERROR" << std::endl;
            return std::nullopt; 
        }

        return result;
    }

    if (argc == 2 && std::string(argv[1]) == "-h")
    {
        PrintHelp();
        return std::nullopt;
    }

    if (argc != 5)
    {
        PrintHelp();
        return std::nullopt;
    }

    result.inputFileName = argv[1];
    result.outputFileName = argv[2];
    result.searchString = argv[3];
    result.replaceString = argv[4];

    return result;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        return (argc == 1) ? 0 : 1;
    }

    bool exitResult = ReplaceStrings(*args);

    return (exitResult) ? 0 : ((argc == 1) ? 0 : 1);
}

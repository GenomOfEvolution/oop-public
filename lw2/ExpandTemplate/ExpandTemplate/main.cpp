#include <iostream>
#include <fstream>
#include <optional>
#include "ExpandTemplate.h"

struct Args
{
    std::map<std::string, std::string> params;
    bool isStdIn = false;
    std::string inputFileName;
    std::string outputFileName;
};

void PrintHelp()
{
    std::cout << "Usage: \n" <<
        "ExpandTemplate.exe <input-file> <output-file> [<param> <value> [<param> <value> ...]] \n" <<
        "OR ExpandTemplate.exe\n" <<
        " [<param> := <value> \\n ...]\n" <<
        " <empty line>\n" <<
        " <lines to replace templates>\n" <<
        "OR ExpandTemplate.exe -h to show this message";
}

std::map<std::string, std::string> ParseParams(std::istream& input)
{
    const std::string DELIMETR = ":=";

    std::map<std::string, std::string> result;
    std::string inputLine;

    while (std::getline(input, inputLine) && !inputLine.empty())
    {
        size_t delimiterPos = inputLine.find(DELIMETR);
        if (delimiterPos == std::string::npos) 
        {
            throw std::runtime_error("Invalid input");
        }

        std::string key = inputLine.substr(0, delimiterPos);
        std::string value = inputLine.substr(delimiterPos + DELIMETR.size());

        key.erase(0, key.find_first_not_of(' '));
        key.erase(key.find_last_not_of(' ') + 1);

        if (key.empty()) 
        {
            continue;
        }

        if (result.find(key) != result.end()) 
        {
            throw std::runtime_error("Non-unique key");
        }

        result[key] = value; 
    }

    return result;
}

std::map<std::string, std::string> ParseCommandLineParams(int argc, char* argv[])
{
    std::map<std::string, std::string> result;

    for (int i = 3; i < argc; i += 2)
    {
        if (std::string(argv[i]).empty())
        {
            continue;
        }

        if (result.find(argv[i]) != result.end())
        {
            throw std::runtime_error("Non-unique key");
        }

        result[argv[i]] = argv[i + 1];
    }

    return result;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args result;

    if (argc == 1)
    {
        result.isStdIn = true;

        try
        {
            result.params = ParseParams(std::cin);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what();
            return std::nullopt;
        }

        return result;
    }

    if (argc == 2 && std::string(argv[1]) == "-h")
    {
        PrintHelp();
        return std::nullopt;
    }

    if (argc % 2 != 1 || argc < 5)
    {
        PrintHelp();
        return std::nullopt;
    }

    try
    {
        result.inputFileName = argv[1];
        result.outputFileName = argv[2];
        result.params = ParseCommandLineParams(argc, argv);

        return result;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return std::nullopt;
}

bool ExpandAllTemplates(const Args& args)
{
    std::ifstream fileInputStream;
    std::ofstream fileOutputStream;

    if (!args.isStdIn)
    {
        fileInputStream.open(args.inputFileName);
        if (!fileInputStream)
        {
            std::cout << "Can't open input file!\n";
            return false;
        }

        fileOutputStream.open(args.outputFileName);
        if (!fileOutputStream)
        {
            std::cout << "Can't open output file" << std::endl;
            return false;
        }
    }

    std::istream& inputStream = args.isStdIn ? std::cin : fileInputStream;
    std::ostream& outputStream = args.isStdIn ? std::cout : fileOutputStream;

    bool wereReadLines = false;
    std::string line;
    while (std::getline(inputStream, line))
    {
        outputStream << ExpandTemplate(line, args.params) << '\n';
        wereReadLines = true;
    }

    if (!wereReadLines)
    {
        std::cout << "No template specified\n";
    }

    return wereReadLines ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);

    if (!args)
    {
        return argc == 2 ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    return ExpandAllTemplates(*args);
}
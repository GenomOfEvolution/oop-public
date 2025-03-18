#include <iostream>
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

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 2)
    {
       
    }
}

int main(int argc, char* argv[])
{
    std::string tpl = "-AABBCCCCCABC+";
    std::map<std::string, std::string> params = {
        {"AA", "[aa]"}, {"BB", "[bb]"}, {"B", "[b]"},
        {"A", "[a]"}, {"CC", "[cc]"}, {"C", "[c]"}
    };

    std::string result = ExpandTemplate(tpl, params);
    std::cout << result << std::endl;

    return 0;
}
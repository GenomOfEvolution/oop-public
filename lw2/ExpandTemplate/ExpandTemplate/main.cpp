#include <iostream>
#include "ExpandTemplate.h"

int main()
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
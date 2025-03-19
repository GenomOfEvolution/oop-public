#include "URL_Parser.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    std::string url;
    std::getline(std::cin, url);

    Protocol protocol;
    int port;
    std::string host, document;

    if (ParseURL(url, protocol, port, host, document)) 
    {
        std::cout << url << "\n";
        std::cout << "HOST: " << host << "\n";
        std::cout << "PORT: " << port << "\n";
        std::cout << "DOC: " << document << "\n";
    }
    else
    {
        std::cout << "ERROR" << std::endl;
    }

    return EXIT_SUCCESS;
}
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

#include <iostream>
#include <unordered_map>

static const std::unordered_map<Protocol, std::string> protocolToString
{
	{ Protocol::HTTP,  "HTTP" },
	{ Protocol::HTTPS, "HTTPS" }
};

void PrintURL(std::ostream& output, const CHttpUrl& url)
{
	output << "URL: " << url.GetURL() << "\n"
		<< "Protocol: " << protocolToString.at(url.GetProtocol()) << "\n"
		<< "Port: " << url.GetPort() << "\n"
		<< "Domain: " << url.GetDomain() << "\n"
		<< "Document: " << url.GetDocument() << "\n";
}

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			PrintURL(std::cout, url);
		}
		catch (const CUrlParsingError& e)
		{
			std::cout << "URL error: " << e.what() << "\n";
		}
		catch (const std::exception& e)
		{
			std::cout << "error: " << e.what() << "\n";
		}
	}

	return EXIT_SUCCESS;
}
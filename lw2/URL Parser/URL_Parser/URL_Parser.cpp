#include "URL_Parser.h"
#include <regex>
#include <map>

void RegexMatch(std::smatch& matches, const std::string& url)
{
    const std::regex urlPattern("^(http[s]?|ftp)://([^:/]+)(?::(\\d+))?(?:/(.*))?$", std::regex::icase);
    std::regex_match(url, matches, urlPattern);
}

bool ParseProtocol(const std::ssub_match& regexProtocol, Protocol& protocol)
{
    static const std::map<std::string, Protocol> protocolMap = 
    {
        { "http", Protocol::HTTP },
        { "https", Protocol::HTTPS },
        { "ftp", Protocol::FTP }
    };

    std::string protocolStr = regexProtocol;
    std::string lowerProtocol;
    lowerProtocol.resize(protocolStr.length());
    std::transform(protocolStr.begin(), protocolStr.end(), lowerProtocol.begin(), ::tolower);

    auto it = protocolMap.find(lowerProtocol);
    if (it != protocolMap.end())
    {
        protocol = it->second;
        return true;
    }

    return false;
}

bool ParseHost(const std::ssub_match& regexHost, std::string& host)
{
    host = regexHost;
    return !host.empty();
}

int GetDefaultPort(const Protocol& protocol)
{
    static const std::map<Protocol, int> protocolToPortMap = 
    {
        { Protocol::HTTP, 80 },
        { Protocol::HTTPS, 443 },
        { Protocol::FTP, 21 }
    };

    auto it = protocolToPortMap.find(protocol);
    if (it != protocolToPortMap.end())
    {
        return it->second;
    }

    return -1;
}

void ParseRegexPort(const std::ssub_match& unparsedRegex, int& port)
{
    try
    {
        port = std::stoi(unparsedRegex);
        if (port < 1 || port > 65535)
        {
            port = -1;
        }
    }
    catch (...)
    {
        port = -1;
    }
}

bool ParsePort(const Protocol& protocol, const std::ssub_match& regexPort, int& port)
{
    port = GetDefaultPort(protocol);
    if (regexPort.matched)
    {
        ParseRegexPort(regexPort, port);
    }

    return (port != -1);
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
    std::smatch matches;
    RegexMatch(matches, url);

    if (!matches.ready())
    {
        return false;
    }

    if (!ParseProtocol(matches[1], protocol))
    {
        return false;
    }

    if (!ParseHost(matches[2], host))
    {
        return false;
    }

    if (!ParsePort(protocol, matches[3], port))
    {
        return false;
    }

    document = matches[4].matched ? matches[4] : std::string();
    return true;
}
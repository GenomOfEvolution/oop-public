#include "CHttpUrl.h"
#include "CUrlParsingError.h"

#include <iostream>
#include <regex>
#include <algorithm>

namespace
{
	constexpr unsigned short DEFAULT_HTTP_PORT = 80;
	constexpr unsigned short DEFAULT_HTTPS_PORT = 443;
	constexpr unsigned short MAX_PORT = 65535;
	constexpr unsigned short MIN_PORT = 1;
}

int ParseInt(const std::string& str)
{
	size_t pos = 0;
	int value = 0;

	try
	{
		value = std::stoi(str, &pos);
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid integer format\n");
	}

	if (pos != str.length())
	{
		throw std::invalid_argument("Invalid integer format\n");
	}

	return value;
}

void RegexMatch(std::smatch& matches, const std::string& url)
{
	const std::regex urlPattern("^(http[s]?)://([^:/]+)(?::(\\d+))?(?:/(.*))?$", std::regex::icase);
	if (!std::regex_match(url, matches, urlPattern))
	{
		throw CUrlParsingError("Failed to parse URL");
	}
}

unsigned short SetBasePort(const Protocol& protocol)
{
	return (protocol == Protocol::HTTPS) ? DEFAULT_HTTPS_PORT : DEFAULT_HTTP_PORT;
}

unsigned short ParsePort(const Protocol& protocol, const std::string& portStr)
{
	if (portStr.empty())
	{
		return SetBasePort(protocol);
	}

	try
	{
		int port = ParseInt(portStr);
		if (port < MIN_PORT || port > MAX_PORT)
		{
			throw std::out_of_range("Port is out of range");
		}

		return port;
	}
	catch (...)
	{
		throw CUrlParsingError("Invalid port");
	}
}

std::string ParseDomain(const std::string& domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Invalid domain");
	}
	return domain;
}

Protocol ParseProtocol(const std::string& protocol)
{
	std::string lowerProtocol = protocol;
	std::transform(lowerProtocol.begin(), lowerProtocol.end(), lowerProtocol.begin(), ::tolower);

	if (lowerProtocol == "https")
	{
		return Protocol::HTTPS;
	}
	else if (lowerProtocol == "http")
	{
		return Protocol::HTTP;
	}

	throw CUrlParsingError("Invalid protocol");
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch matches;
	RegexMatch(matches, url);

	m_protocol = ParseProtocol(matches[1]);
	m_domain = ParseDomain(matches[2]);
	m_port = ParsePort(m_protocol, matches[3]);

	m_document = "/";
	m_document += matches[4].matched ? matches[4] : std::string();

	m_url = FormUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	try
	{
		m_domain = ParseDomain(domain);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument(e.what());
	}
	
	m_document = document;
	m_protocol = protocol;
	m_port = (protocol == Protocol::HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
	m_url = FormUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	try
	{
		m_domain = ParseDomain(domain);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument(e.what());
	}

	m_document = document;
	m_protocol = protocol;
	if (port < MIN_PORT)
	{
		throw std::invalid_argument("Port must be greater between 0 and 65535");
	}
	m_port = port;
	m_url = FormUrl();
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

bool IsDefaultPortProtocol(Protocol protocol, unsigned short port)
{
	return (protocol == Protocol::HTTP && port == DEFAULT_HTTP_PORT) ||
		(protocol == Protocol::HTTPS && port == DEFAULT_HTTPS_PORT);
}

std::string CHttpUrl::FormUrl() const
{
	std::string url;

	url += (m_protocol == Protocol::HTTP) ? "http://" : "https://";
	url += m_domain;
	url += IsDefaultPortProtocol(m_protocol, m_port) ? "" : (":" + std::to_string(m_port));
	url += m_document;

	return url;
}

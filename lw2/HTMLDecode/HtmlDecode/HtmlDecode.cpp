#include "HtmlDecode.h"
#include <map>
#include <iterator>

std::string ChooseHtmlEntity(const std::string& str)
{
	static std::map<std::string, std::string> specialChar 
	{
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&gt;", ">" },
		{ "&lt;", "<" },
		{ "&amp;", "&" } 
	};

	for (auto [key, value] : specialChar)
	{
		if (key == str)
		{
			return value;
		}
	}

	return str;
}

std::string HtmlDecode(const std::string& html)
{
	if (html.empty())
	{
		return html;
	}

	const char START_HTML_ENTITY = '&';
	const char END_HTML_ENTITY = ';';

	if (
		html.find(START_HTML_ENTITY) == std::string::npos ||
		html.find(END_HTML_ENTITY) == std::string::npos
	)
	{
		return html;
	}

	std::string decoded;
	size_t HtmlStartPos = 0;
	size_t HtmlEndPos = 0;
	size_t curPos = 0;

	// нейминг и оформление
	while (html.find(START_HTML_ENTITY, HtmlEndPos) != std::string::npos)
	{
		HtmlStartPos = html.find(START_HTML_ENTITY, HtmlEndPos);
		HtmlEndPos = html.find(END_HTML_ENTITY, HtmlStartPos);

		std::copy(html.begin() + curPos, html.begin() + HtmlStartPos, std::back_inserter(decoded));
		std::string htmlEntry;
		std::copy(html.begin() + HtmlStartPos, html.begin() + HtmlEndPos + 1, std::back_inserter(htmlEntry));

		decoded += ChooseHtmlEntity(htmlEntry);
		curPos = HtmlEndPos + 1;
	}

	std::copy(html.begin() + curPos, html.end(), std::back_inserter(decoded));

	return decoded;
}

void DecodeHtmlEntites(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << HtmlDecode(line);
	}
}

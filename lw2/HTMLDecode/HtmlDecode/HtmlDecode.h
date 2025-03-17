#pragma once
#include <iostream>
#include <string>

std::string HtmlDecode(std::string const& html);
void DecodeHtmlEntites(std::istream& input, std::ostream& output);
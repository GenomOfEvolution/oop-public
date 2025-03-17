#pragma once
#include <string>
#include <map>

std::string ExpandTemplate(const std::string& tpl, const std::map<std::string, std::string>& params);
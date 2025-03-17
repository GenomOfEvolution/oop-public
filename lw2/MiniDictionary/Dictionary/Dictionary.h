#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <optional>
#include <algorithm>
#include <cctype>

using Dictionary = std::multimap<std::string, std::string>;

struct Args
{
    std::string fileName;
};

void ReadDictionary(const std::string& inputName, Dictionary& ruToEn, Dictionary& enToRu);
void SaveDictionary(const std::string& outputName, const Dictionary& ruToEn);
void HandleUnknownWord(const std::string& word, Dictionary& ruToEn, Dictionary& enToRu, bool& changesMade);
std::string FormatTranslations(const std::pair<Dictionary::iterator, Dictionary::iterator>& range);
void WorkWithDictionary(const Args& args);
std::optional<Args> ParseArgs(int argc, char* argv[]);
std::string ToLower(const std::string& str);
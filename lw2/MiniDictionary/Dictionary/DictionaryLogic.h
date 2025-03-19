#pragma once
#include <map>
#include <string>
#include <optional>

using Dictionary = std::multimap<std::string, std::string>;

void LoadDictionary(const std::string& fileName, Dictionary& ruToEn, Dictionary& enToRu);
void SaveDictionary(const std::string& fileName, const Dictionary& ruToEn);
std::optional<std::string> FindTranslations(const Dictionary& dict, const std::string& word);
void AddTranslation(Dictionary& ruToEn, Dictionary& enToRu, const std::string& word, const std::string& translation);
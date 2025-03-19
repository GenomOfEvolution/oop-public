#include "DictionaryLogic.h"
#include <fstream>

void LoadDictionary(const std::string& fileName, Dictionary& ruToEn, Dictionary& enToRu) 
{
    std::ifstream input(fileName);
    if (!input) 
    {
        return;
    }

    std::string word, translation;
    while (std::getline(input, word) && std::getline(input, translation)) 
    {
        ruToEn.insert({ word, translation });
        enToRu.insert({ translation, word });
    }
}

void SaveDictionary(const std::string& fileName, const Dictionary& ruToEn) 
{
    std::ofstream output(fileName);
    if (!output) 
    {
        return;
    }

    for (const auto& entry : ruToEn) {
        output << entry.first << "\n" << entry.second << "\n";
    }
}

std::optional<std::string> FindTranslations(const Dictionary& dict, const std::string& word) 
{
    auto range = dict.equal_range(word);
    if (range.first == range.second) 
    {
        return std::nullopt;
    }

    std::string translations;
    for (auto it = range.first; it != range.second; ++it) 
    {
        if (!translations.empty()) 
        {
            translations += ", ";
        }
        translations += it->second;
    }
    return translations;
}

void AddTranslation(Dictionary& ruToEn, Dictionary& enToRu, const std::string& word, const std::string& translation) 
{
    ruToEn.insert({ word, translation });
    enToRu.insert({ translation, word });
}
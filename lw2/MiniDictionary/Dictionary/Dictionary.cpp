#include "Dictionary.h"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: Dictionary.exe <dictionary file>\n";
        return std::nullopt;
    }

    Args result;
    result.fileName = argv[1];
    return result;
}

std::string ToLower(const std::string& str)
{
    std::string result;
    for (unsigned char ch : str)
    {
        result.push_back(std::tolower(ch));
    }
    return result;
}

void ReadDictionary(const std::string& inputName, Dictionary& ruToEn, Dictionary& enToRu)
{
    std::ifstream input(inputName);
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

void SaveDictionary(const std::string& outputName, const Dictionary& ruToEn)
{
    std::ofstream output(outputName);
    if (!output)
    {
        std::cout << "Ошибка при сохранении словаря.\n";
        return;
    }

    for (const auto& entry : ruToEn)
    {
        output << entry.first << "\n" << entry.second << "\n";
    }
}

void HandleUnknownWord(const std::string& word, Dictionary& ruToEn, Dictionary& enToRu, bool& changesMade)
{
    std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n";
    std::string translation;
    std::getline(std::cin, translation);

    if (!translation.empty())
    {
        ruToEn.insert({ word, translation });
        enToRu.insert({ translation, word });
        changesMade = true;
        std::cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\".\n";
    }
    else
    {
        std::cout << "Слово \"" << word << "\" проигнорировано.\n";
    }
}

std::string FormatTranslations(const std::pair<Dictionary::iterator, Dictionary::iterator>& range)
{
    std::string translations;
    for (auto it = range.first; it != range.second; ++it)
    {
        translations += it->second + ", ";
    }
    if (!translations.empty())
    {
        translations.pop_back();
        translations.pop_back();
    }
    return translations;
}

void HandleDictionary(const Args& args)
{
    Dictionary ruToEn;
    Dictionary enToRu;

    ReadDictionary(args.fileName, ruToEn, enToRu);

    WorkWithDictionary(ruToEn, enToRu);
}

// выделить логику работы со словарем только в этом модуле

void WorkWithDictionary(Dictionary& ruToEn, Dictionary enToRu)
{
    bool changesMade = false;

    while (true)
    {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "...")
        {
            if (changesMade)
            {
                std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
                std::string saveChoice;
                std::getline(std::cin, saveChoice);
                if (saveChoice == "Y" || saveChoice == "y")
                {
                    SaveDictionary(args.fileName, ruToEn);
                    std::cout << "Изменения сохранены. До свидания.\n";
                }
            }
            break;
        }

        auto ruToEnRange = ruToEn.equal_range(input);
        if (ruToEnRange.first != ruToEnRange.second)
        {
            std::cout << FormatTranslations(ruToEnRange) << "\n";
            continue;
        }

        auto enToRuRange = enToRu.equal_range(input);
        if (enToRuRange.first != enToRuRange.second)
        {
            std::cout << FormatTranslations(enToRuRange) << "\n";
            continue;
        }

        HandleUnknownWord(input, ruToEn, enToRu, changesMade);
    }
}

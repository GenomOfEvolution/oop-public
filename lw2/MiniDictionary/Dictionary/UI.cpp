#include "UI.h"
#include "DictionaryLogic.h"
#include <iostream>

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

void RunUI(const std::string& fileName) 
{
    Dictionary ruToEn;
    Dictionary enToRu;
    LoadDictionary(fileName, ruToEn, enToRu);

    bool changesMade = false;

    while (true) 
    {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "...") 
        {
            if (changesMade) 
            {
                std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
                std::string saveChoice;
                std::getline(std::cin, saveChoice);
                if (saveChoice == "Y" || saveChoice == "y") {
                    SaveDictionary(fileName, ruToEn);
                    std::cout << "Изменения сохранены. До свидания.\n";
                }
            }
            break;
        }

        auto translations = FindTranslations(ruToEn, input);
        if (!translations) 
        {
            translations = FindTranslations(enToRu, input);
        }

        if (translations) 
        {
            std::cout << *translations << "\n";
        }
        else 
        {
            std::cout << "Неизвестное слово \"" << input << "\". Введите перевод или пустую строку для отказа.\n";
            std::string translation;
            std::getline(std::cin, translation);

            if (!translation.empty()) 
            {
                AddTranslation(ruToEn, enToRu, input, translation);
                changesMade = true;
                std::cout << "Слово \"" << input << "\" сохранено в словаре как \"" << translation << "\".\n";
            }
            else 
            {
                std::cout << "Слово \"" << input << "\" проигнорировано.\n";
            }
        }
    }
}
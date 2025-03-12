#include "Trie.h"
#include <iostream>
#include <map>
#include <vector>

std::vector<std::pair<size_t, size_t>> FindAllMatches(const std::string& text, Trie& trie)
{
    std::vector<std::pair<size_t, size_t>> matches;
    Node* current = trie.root;

    for (size_t i = 0; i < text.size(); ++i)
    {
        char ch = text[i];
        while (current != nullptr && current->FindChild(ch) == nullptr)
        {
            current = current->suffixLink;
        }
        if (current == nullptr)
        {
            current = trie.root;
            continue;
        }
        current = current->FindChild(ch);

        // Проверяем, является ли текущий узел терминальным
        if (current->isTerminal)
        {
            std::string word = current->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;
            matches.emplace_back(start, end);
        }

        // Проверяем выходные ссылки
        Node* output = current->outputLink;
        while (output != nullptr)
        {
            std::string word = output->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;
            matches.emplace_back(start, end);
            output = output->outputLink;
        }
    }

    return matches;
}

std::vector<std::pair<size_t, size_t>> FilterLongestMatches(const std::vector<std::pair<size_t, size_t>>& matches, size_t textLength)
{
    // Сортируем совпадения по длине (от большего к меньшему)
    auto sortedMatches = matches;
    std::sort(sortedMatches.begin(), sortedMatches.end(), [](const auto& a, const auto& b) {
        return (a.second - a.first) > (b.second - b.first);
        });

    // Убираем перекрывающиеся совпадения
    std::vector<bool> used(textLength, false);
    std::vector<std::pair<size_t, size_t>> longestMatches;

    for (const auto& match : sortedMatches)
    {
        size_t start = match.first;
        size_t end = match.second;
        bool canAdd = true;

        // Проверяем, не перекрывается ли текущее совпадение с уже использованными символами
        for (size_t i = start; i < end; ++i)
        {
            if (used[i])
            {
                canAdd = false;
                break;
            }
        }

        if (canAdd)
        {
            longestMatches.push_back(match);
            for (size_t i = start; i < end; ++i)
            {
                used[i] = true;
            }
        }
    }

    return longestMatches;
}

std::map<std::string, std::vector<size_t>> SearchLongestMatches(const std::string& text, Trie& trie)
{
    std::map<std::string, std::vector<size_t>> occurrences;

    // Находим все совпадения
    auto allMatches = FindAllMatches(text, trie);

    // Фильтруем совпадения, оставляя только самые длинные
    auto longestMatches = FilterLongestMatches(allMatches, text.size());

    // Записываем результаты
    for (const auto& match : longestMatches)
    {
        size_t start = match.first;
        size_t end = match.second;
        std::string word = text.substr(start, end - start);
        occurrences[word].push_back(start);
    }

    return occurrences;
}


std::map<std::string, std::vector<size_t>> SearchLongestMatchesOnTheFly(const std::string& text, Trie& trie)
{
    std::map<std::string, std::vector<size_t>> occurrences;
    std::vector<size_t> longestMatchEnd(text.size(), 0); // Хранит конец самого длинного совпадения для каждой позиции

    Node* current = trie.root;
    for (size_t i = 0; i < text.size(); ++i)
    {
        char ch = text[i];
        while (current != nullptr && current->FindChild(ch) == nullptr)
        {
            current = current->suffixLink;
        }
        if (current == nullptr)
        {
            current = trie.root;
            continue;
        }
        current = current->FindChild(ch);

        // Проверяем, является ли текущий узел терминальным
        if (current->isTerminal)
        {
            std::string word = current->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;

            // Если текущее совпадение длиннее предыдущего для этой позиции
            if (end > longestMatchEnd[start])
            {
                longestMatchEnd[start] = end;
                occurrences[word].push_back(start);
            }
        }

        // Проверяем выходные ссылки
        Node* output = current->outputLink;
        while (output != nullptr)
        {
            std::string word = output->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;

            // Если текущее совпадение длиннее предыдущего для этой позиции
            if (end > longestMatchEnd[start])
            {
                longestMatchEnd[start] = end;
                occurrences[word].push_back(start);
            }
            output = output->outputLink;
        }
    }

    return occurrences;
}

int main()
{
    Trie trie;
    std::vector<std::string> words = { "A", "AA", "B", "BB", "C", "CC" };

    // Вставляем слова в бор
    for (const std::string& word : words)
    {
        trie.Insert(word);
    }

    // Строим суффиксные ссылки
    trie.BuildSuffixLinks();

    // Текст для обработки
    std::string text = "-AABBCCCCCABC+";

    // Поиск самых длинных неперекрывающихся совпадений
    auto occurrences = SearchLongestMatches(text, trie);

    // Вывод результатов
    for (const auto& pair : occurrences)
    {
        std::cout << "Word: " << pair.first << ", Positions: ";
        for (size_t pos : pair.second)
        {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
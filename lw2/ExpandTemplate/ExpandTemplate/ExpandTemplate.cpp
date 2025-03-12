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

        // ���������, �������� �� ������� ���� ������������
        if (current->isTerminal)
        {
            std::string word = current->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;
            matches.emplace_back(start, end);
        }

        // ��������� �������� ������
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
    // ��������� ���������� �� ����� (�� �������� � ��������)
    auto sortedMatches = matches;
    std::sort(sortedMatches.begin(), sortedMatches.end(), [](const auto& a, const auto& b) {
        return (a.second - a.first) > (b.second - b.first);
        });

    // ������� ��������������� ����������
    std::vector<bool> used(textLength, false);
    std::vector<std::pair<size_t, size_t>> longestMatches;

    for (const auto& match : sortedMatches)
    {
        size_t start = match.first;
        size_t end = match.second;
        bool canAdd = true;

        // ���������, �� ������������� �� ������� ���������� � ��� ��������������� ���������
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

    // ������� ��� ����������
    auto allMatches = FindAllMatches(text, trie);

    // ��������� ����������, �������� ������ ����� �������
    auto longestMatches = FilterLongestMatches(allMatches, text.size());

    // ���������� ����������
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
    std::vector<size_t> longestMatchEnd(text.size(), 0); // ������ ����� ������ �������� ���������� ��� ������ �������

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

        // ���������, �������� �� ������� ���� ������������
        if (current->isTerminal)
        {
            std::string word = current->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;

            // ���� ������� ���������� ������� ����������� ��� ���� �������
            if (end > longestMatchEnd[start])
            {
                longestMatchEnd[start] = end;
                occurrences[word].push_back(start);
            }
        }

        // ��������� �������� ������
        Node* output = current->outputLink;
        while (output != nullptr)
        {
            std::string word = output->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;

            // ���� ������� ���������� ������� ����������� ��� ���� �������
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

    // ��������� ����� � ���
    for (const std::string& word : words)
    {
        trie.Insert(word);
    }

    // ������ ���������� ������
    trie.BuildSuffixLinks();

    // ����� ��� ���������
    std::string text = "-AABBCCCCCABC+";

    // ����� ����� ������� ����������������� ����������
    auto occurrences = SearchLongestMatches(text, trie);

    // ����� �����������
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
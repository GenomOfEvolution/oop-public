#include "Trie.h"
#include "ExpandTemplate.h"

#include <iostream>
#include <vector>
#include <algorithm>

struct Match
{
    size_t start;
    size_t end;
    std::string word;
};

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

        if (current->isTerminal)
        {
            std::string word = current->outputWord;
            size_t start = i - word.size() + 1;
            size_t end = i + 1;
            matches.emplace_back(start, end);
        }

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
    auto sortedMatches = matches;
    std::sort(sortedMatches.begin(), sortedMatches.end(), [](const auto& a, const auto& b) {
        return (a.second - a.first) > (b.second - b.first);
        });

    std::vector<bool> used(textLength, false);
    std::vector<std::pair<size_t, size_t>> longestMatches;

    for (const auto& [start, end] : sortedMatches)
    {
        bool canAdd = true;

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
            longestMatches.push_back({ start, end });
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

    auto allMatches = FindAllMatches(text, trie);
    auto longestMatches = FilterLongestMatches(allMatches, text.size());

    for (const auto& [start, end] : longestMatches)
    {
        std::string word = text.substr(start, end - start);
        occurrences[word].push_back(start);
    }

    return occurrences;
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
    Trie trie;
    for (const auto& [key, value] : params)
    {
        trie.Insert(key);
    }

    trie.BuildSuffixLinks();

    auto occurrences = SearchLongestMatches(tpl, trie);

    std::vector<Match> matches;
    for (const auto& [word, starts] : occurrences)
    {
        for (size_t start : starts)
        {
            size_t end = start + word.length();
            matches.push_back({ start, end, word });
        }
    }

    std::sort(matches.begin(), matches.end(), [](const Match& a, const Match& b) {
        return a.start < b.start;
        });

    std::string result;
    size_t currentPos = 0;
    for (const auto& match : matches)
    {
        if (match.start > currentPos)
        {
            result += tpl.substr(currentPos, match.start - currentPos);
        }
        result += params.at(match.word);
        currentPos = match.end;
    }

    if (currentPos < tpl.length())
    {
        result += tpl.substr(currentPos);
    }

    return result;
}
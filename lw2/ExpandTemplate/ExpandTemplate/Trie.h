#pragma once
#include <set>
#include <string>

struct Node
{
    char value;
    bool isTerminal = false;
    std::set<Node*> children;
    Node* suffixLink = nullptr;
    Node* outputLink = nullptr; 

    Node(char ch = '\0') : value(ch) {}
    void Insert(char ch, bool isTerminal);
    Node* FindChild(char ch);
};

struct Trie
{
    Node* root = new Node();

    void Insert(const std::string& str);
    void BuildSuffixLinks();
};
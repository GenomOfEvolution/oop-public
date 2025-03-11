#include "Trie.h"
#include <algorithm> 

void Node::Insert(char ch, bool isTerminal)
{
    auto it = std::find_if(children.begin(), children.end(), [ch](Node* node) { return node->value == ch; });

    if (it != children.end())
    {
        if (isTerminal)
        {
            (*it)->isTerminal = true;
        }
    }
    else
    {
        Node* newNode = new Node(ch);
        newNode->isTerminal = isTerminal;
        children.insert(newNode);
    }
}

Node* Node::FindChild(char ch)
{
    auto it = std::find_if(children.begin(), children.end(), [ch](Node* node) { return node->value == ch; });
    return (it != children.end()) ? *it : nullptr;
}

void Trie::Insert(const std::string& str)
{
    Node* current = root;
    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        bool isTerminal = (i == str.size() - 1);
        current->Insert(ch, isTerminal);
        current = current->FindChild(ch);
    }
}
#include "Trie.h"
#include <algorithm> 
#include <queue>

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

void Trie::BuildSuffixLinks()
{
    std::queue<Node*> q;
    for (Node* child : root->children)
    {
        q.push(child);
        child->suffixLink = root;
    }

    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();

        for (Node* child : current->children)
        {
            q.push(child);
            Node* temp = current->suffixLink;

            while (temp != nullptr && temp->FindChild(child->value) == nullptr)
            {
                temp = temp->suffixLink;
            }

            if (temp == nullptr)
            {
                child->suffixLink = root;
            }
            else
            {
                child->suffixLink = temp->FindChild(child->value);
            }

            if (child->suffixLink->isTerminal)
            {
                child->outputLink = child->suffixLink;
            }
            else
            {
                child->outputLink = child->suffixLink->outputLink;
            }
        }
    }
}
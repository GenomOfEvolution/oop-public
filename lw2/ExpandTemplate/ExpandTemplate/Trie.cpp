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
        if (isTerminal)
        {
            current->outputWord = str; // Сохраняем слово в терминальном узле
        }
    }
}

void Trie::BuildSuffixLinks()
{
    std::queue<Node*> q;
    for (Node* child : root->children)
    {
        q.push(child);
        child->suffixLink = root; // Суффиксная ссылка для детей корня ведет в корень
    }

    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();

        for (Node* child : current->children)
        {
            q.push(child);
            Node* temp = current->suffixLink;

            // Ищем суффиксную ссылку для child
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

            // Устанавливаем выходную ссылку
            if (child->suffixLink != nullptr && child->suffixLink->isTerminal)
            {
                // Если суффиксная ссылка ведет на терминальный узел, то это выходная ссылка
                child->outputLink = child->suffixLink;
            }
            else
            {
                // Иначе копируем выходную ссылку из суффиксной ссылки
                child->outputLink = (child->suffixLink != nullptr) ? child->suffixLink->outputLink : nullptr;
            }
        }
    }
}
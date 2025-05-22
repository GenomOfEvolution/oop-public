#include "CStringList.h"
#include <stdexcept>
#include <utility>

CStringList::CStringList(const CStringList& other)
{
    if (&other == this) 
    {
        return;
    }

    for (const auto& item : other) 
    {
        PushBack(item);
    }
}

CStringList::CStringList(CStringList&& other) noexcept
    : m_head(std::move(other.m_head))
    , m_tail(other.m_tail)
    , m_size(other.m_size)
{
    other.m_tail = nullptr;
    other.m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& other)
{
    if (this != &other) 
    {
        CStringList temp(other);
        Swap(temp);
    }
    return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
    if (this != &other) 
    {
        Clear();
        m_head = std::move(other.m_head);
        m_tail = other.m_tail;
        m_size = other.m_size;
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    return *this;
}

CStringList::~CStringList()
{
	Clear();
}

void CStringList::PushBack(const std::string& str)
{
    auto newNode = std::make_unique<Node>(str, nullptr, m_tail);
    if (m_tail) 
    {
        m_tail->next = std::move(newNode);
        m_tail = m_tail->next.get();
    }
    else 
    {
        m_head = std::move(newNode);
        m_tail = m_head.get();
    }
    ++m_size;
}

void CStringList::PushFront(const std::string& str)
{
    auto newNode = std::make_unique<Node>(str, std::move(m_head), nullptr);

    if (m_head)
    {
        m_head->prev = newNode.get();
    }
    else
    {
        m_tail = newNode.get();
    }

    m_head = std::move(newNode);  
    ++m_size;
}

size_t CStringList::Size() const noexcept
{
    return m_size;
}

bool CStringList::Empty() const noexcept
{
    return m_size == 0;
}

void CStringList::Clear() noexcept
{
    while (m_head) 
    {
        auto next = std::move(m_head->next);
        m_head.reset();
        m_head = std::move(next);
    }

    m_tail = nullptr;
    m_size = 0;
}

void CStringList::Insert(ConstIterator pos, const std::string& value)
{
    if (pos == cbegin()) 
    {
        PushFront(value);
        return;
    }

    if (pos == cend()) 
    {
        PushBack(value);
        return;
    }

    /*Node* nodeAtPos = const_cast<Node*>(pos.m_node);
    auto newNode = std::make_unique<Node>(value, std::move(nodeAtPos->prev->next), nodeAtPos->prev);
    newNode->prev->next = std::move(nodeAtPos->prev);
    nodeAtPos->prev = newNode.get();
    ++m_size;*/
}

void CStringList::Delete(ConstIterator pos) 
{
    if (pos == cend()) 
    {
        throw std::out_of_range("Cannot delete end iterator");
    }

    Node* nodeToDelete = const_cast<Node*>(pos.m_node);
    std::unique_ptr<Node>* prevNextPtr = nullptr;

    if (nodeToDelete == m_head.get()) 
    {
        prevNextPtr = &m_head;
    }
    else 
    {
        prevNextPtr = &(nodeToDelete->prev->next);
    }

    if (nodeToDelete == m_tail) 
    {
        m_tail = nodeToDelete->prev;
    }
    else 
    {
        Node* nextNode = nodeToDelete->next.get();
        nextNode->prev = nodeToDelete->prev;
    }

    *prevNextPtr = std::move(nodeToDelete->next);
    --m_size;
}

void CStringList::Insert(Iterator pos, const std::string& value)
{
    Insert(ConstIterator(pos.m_node), value);
}

void CStringList::Delete(Iterator pos)
{
    Delete(ConstIterator(pos.m_node));
}

void CStringList::Swap(CStringList& other) noexcept
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

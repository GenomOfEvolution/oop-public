#pragma once
#include <string>
#include <memory>
#include <iterator>

class CStringList
{
public:
    CStringList() = default;
    CStringList(const CStringList& other);
    CStringList(CStringList&& other) noexcept;
    CStringList& operator=(const CStringList& other);
    CStringList& operator=(CStringList&& other) noexcept;
    ~CStringList();

    void PushBack(const std::string& str);
    void PushFront(const std::string& str);

    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void Clear() noexcept;

    struct Node
    {
        std::string data;
        std::unique_ptr<Node> next;
        Node* prev = nullptr;
    };

    class Iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = std::string*;
        using reference = std::string&;

        Iterator() = default;
        explicit Iterator(Node* node) : m_node(node) {}

        reference operator*() const { return m_node->data; }
        pointer operator->() const { return &m_node->data; }

        Iterator& operator++() 
        {
            m_node = m_node->next.get();
            return *this;
        }

        Iterator operator++(int) 
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() 
        {
            m_node = m_node->prev;
            return *this;
        }

        Iterator operator--(int) 
        {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        Node* m_node = nullptr;
        friend class CStringList;
    };

    class ConstIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = const std::string*;
        using reference = const std::string&;

        ConstIterator() = default;
        explicit ConstIterator(const Node* node) : m_node(node) {}

        reference operator*() const { return m_node->data; }
        pointer operator->() const { return &m_node->data; }

        ConstIterator& operator++() 
        {
            m_node = m_node->next.get();
            return *this;
        }

        ConstIterator operator++(int) 
        {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ConstIterator& operator--() 
        {
            m_node = m_node->prev;
            return *this;
        }

        ConstIterator operator--(int) 
        {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const ConstIterator& other) const { return m_node == other.m_node; }
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }

    private:
        const Node* m_node = nullptr;
        friend class CStringList;
    };

    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

    Iterator begin() noexcept { return Iterator(m_head.get()); }
    Iterator end() noexcept { return Iterator(nullptr); }

    ConstIterator begin() const noexcept { return ConstIterator(m_head.get()); }
    ConstIterator end() const noexcept { return ConstIterator(nullptr); }           // TODO: проверить end--

    ConstIterator cbegin() const noexcept { return begin(); }
    ConstIterator cend() const noexcept { return end(); }

    ReverseIterator rbegin() noexcept { return ReverseIterator(end()); }
    ReverseIterator rend() noexcept { return ReverseIterator(begin()); }

    ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); }
    ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); }

    ConstReverseIterator crbegin() const noexcept { return rbegin(); }
    ConstReverseIterator crend() const noexcept { return rend(); }

    void Insert(ConstIterator pos, const std::string& value);
    void Delete(ConstIterator pos);
    void Insert(Iterator pos, const std::string& value);
    void Delete(Iterator pos);

private:
    std::unique_ptr<Node> m_head = nullptr;
    Node* m_tail = nullptr;
    size_t m_size = 0;

    void Swap(CStringList& other) noexcept;
};
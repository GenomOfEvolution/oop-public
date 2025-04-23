#pragma once
#include <string>
#include <iostream>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(std::string const& stlString);

    ~CMyString();

    [[nodiscard]] size_t GetLength() const;
    [[nodiscard]] size_t GetCapacity() const;

    const char* GetStringData() const;
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear();
    
    // Operators
    bool operator==(const CMyString& rhs) const noexcept;
    std::strong_ordering operator<=>(const CMyString& rhs) const noexcept;

    CMyString& operator=(const CMyString& other);
    CMyString& operator=(CMyString&& other) noexcept;

    CMyString operator+(const CMyString& other) const;
    CMyString operator+(const std::string& other) const;
    CMyString operator+(const char* other) const;

    CMyString& operator+=(const CMyString& other);

    const char& operator[](size_t index) const;
    char& operator[](size_t index);

    friend std::ostream& operator<<(std::ostream& os, const CMyString& str);
    friend std::istream& operator>>(std::istream& is, CMyString& str);

    // Iterators

    using Iterator = char*;
    using ConstIterator = const char*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

    Iterator begin() noexcept { return m_chars; }
    Iterator end() noexcept { return m_chars + m_size; }

    ConstIterator begin() const noexcept { return m_chars; }
    ConstIterator end() const noexcept { return m_chars + m_size; }

    ConstIterator cbegin() const noexcept { return begin(); }  
    ConstIterator cend() const noexcept { return end(); }     

    ReverseIterator rbegin() noexcept { return ReverseIterator(end()); }
    ReverseIterator rend() noexcept { return ReverseIterator(begin()); }

    ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); }
    ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); }

    ConstReverseIterator crbegin() const noexcept { return rbegin(); }  
    ConstReverseIterator crend() const noexcept { return rend(); }

private:
    inline static char s_emptyString[] = {'\0'};

    size_t m_capacity = 0;
    size_t m_size = 0;
    char* m_chars;
};
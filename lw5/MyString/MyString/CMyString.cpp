#include "CMyString.h"
#include <cstring>
#include <compare>
#include <utility>

char* AllocateMemory(size_t size)
{
	return new char[size]();
}

void ReleaseMemory(const char* chars)
{
	delete[] chars;
}

CMyString::CMyString()
	: m_size(0)
	, m_capacity(1)
	, m_chars(s_emptyString)
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_size = length;
	m_capacity = (length == 0) ? 1 : length + 1;
	m_chars = (length == 0) ? s_emptyString : AllocateMemory(m_capacity);

	// отловить std::bad_alloc
	try
	{
		if (length > 0)
		{
			std::uninitialized_copy_n(pString, length, m_chars);
		}
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Can`t allocate memory!";
	}

	m_chars[m_size] = '\0'; 
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_chars, other.m_size)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_size(std::exchange(other.m_size, 0)),
	m_capacity(std::exchange(other.m_capacity, 1)),
	m_chars(std::exchange(other.m_chars, s_emptyString))
{
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	if (m_chars != s_emptyString)
	{
		ReleaseMemory(m_chars);
	}
}

size_t CMyString::GetLength() const
{
	return m_size;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

const char* CMyString::GetStringData() const
{
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (length >= m_size)
	{
		throw std::out_of_range("Invalid start pos");
	}
	size_t lengthToCopy = std::min(length, m_size - length);

	return CMyString(m_chars + start, lengthToCopy);
}

void CMyString::Clear()
{
	if (m_chars != s_emptyString)
	{
		ReleaseMemory(m_chars);
	}

	m_chars = s_emptyString;
	m_size = 0;
	m_capacity = 1;
}

bool CMyString::operator==(const CMyString& rhs) const noexcept
{
	if (m_chars == rhs.m_chars)
		return true;

	if (m_size != rhs.m_size)
		return false;

	return strcmp(m_chars, rhs.m_chars) == 0;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_size && m_chars != s_emptyString)
		{
			std::destroy_n(m_chars, m_size + 1);

			// тоже exception
			try
			{
				std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
			}
			catch (const std::bad_alloc& e)
			{
				std::cout << "Can`t allocte memory!";
			}
			
			m_size = other.m_size;
		}
		else
		{
			CMyString copy{ other };
			std::swap(m_size, copy.m_size);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_chars, copy.m_chars);
		}
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other) 
	{
		if (m_chars != s_emptyString)
		{
			ReleaseMemory(m_chars);
		}

		m_size = std::exchange(other.m_size, 0);
		m_capacity = std::exchange(other.m_capacity, 1);
		m_chars = std::exchange(other.m_chars, s_emptyString);
	}
	return *this;
}

CMyString CMyString::operator+(const CMyString& other) const
{
	CMyString result;

	result.m_size = m_size + other.m_size;
	result.m_capacity = result.m_size + 1;

	result.m_chars = AllocateMemory(result.m_capacity);
	std::memcpy(result.m_chars, m_chars, m_size);
	std::memcpy(result.m_chars + m_size, other.m_chars, other.m_size);
	result.m_chars[result.m_size] = '\0';

	return result;
}

CMyString CMyString::operator+(const std::string& other) const
{
	return *this + CMyString(other);
}

CMyString CMyString::operator+(const char* other) const
{
	return *this + CMyString(other);
}

// опционально сделать через оператор +
CMyString& CMyString::operator+=(const CMyString& other)
{
	if (other.m_size + m_size >= m_capacity)
	{
		m_capacity = std::max(other.m_size + m_size + 1, m_capacity * 2);

		auto chars = AllocateMemory(m_capacity);
		std::memcpy(chars, m_chars, m_size);
		m_chars = chars;
	}

	std::memcpy(m_chars + m_size, other.m_chars, other.m_size + 1);
	m_size = m_size + other.m_size;

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_chars[index];
}

std::strong_ordering CMyString::operator<=>(const CMyString& rhs) const noexcept
{
	if (m_chars == rhs.m_chars)
		return std::strong_ordering::equal;

	return strcmp(m_chars, rhs.m_chars) <=> 0;
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
	return os << str.m_chars;
}

// через get, выставить failbit если не удалось
std::istream& operator>>(std::istream& is, CMyString& str)
{
	std::string word;
	is >> word;
	str = CMyString(word);
	return is;
}
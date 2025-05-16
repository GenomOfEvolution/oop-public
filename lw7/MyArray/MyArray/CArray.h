#pragma once

template <typename T>
class CArray
{
public:
	CArray();
	~CArray() noexcept;

	CArray(const CArray& other);
	CArray(CArray&& other) noexcept;

	void Push(const T& item);
	size_t Size();
	size_t Capacity();

	void Resize(size_t newSize);
	void Clear() noexcept;

	CArray<T>& operator=(const CArray& other);
	CArray<T>& operator=(CArray&& other) noexcept;

	T& operator[](size_t index);
	T const& operator[](size_t index) const;

	// Iterators
	using Iterator = T*;
	using ConstIterator = const T*;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() noexcept { return m_data; }
	ConstIterator begin() const noexcept { return m_data; }
	Iterator end() noexcept { return m_data + m_size; }
	ConstIterator end() const noexcept { return m_data + m_size; }

	ReverseIterator rbegin() noexcept { return ReverseIterator(end()); }
	ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); }
	ReverseIterator rend() noexcept { return ReverseIterator(begin()); }
	ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); }

	// bonus
	template <typename U>
	CArray<T>& operator=(const CArray<U>& other);

private:
	void Allocate(size_t size);
	void Swap(CArray& other) noexcept;

	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};

// сделать дефолтным
template <typename T>
CArray<T>::CArray()
	: m_capacity(0)
	, m_size(0)
	, m_data(nullptr)
{
}

template <typename T>
CArray<T>::~CArray() noexcept
{
	Clear();
}

template<typename T>
CArray<T>::CArray(const CArray& other)
	: m_capacity(other.m_capacity)
	, m_size(other.m_size)
{
	// try catch для bad_alloc
	T* temp = nullptr;
	if (other.m_data != nullptr)
	{
		temp = new T[m_size];
		std::copy(other.m_data, other.m_data + m_size, temp);
	}
	m_data = temp;
}

template<typename T>
CArray<T>::CArray(CArray&& other) noexcept
	: m_data(other.m_data)
	, m_capacity(other.m_capacity)
	, m_size(other.m_size)
{
	// Swap
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;
}

template<typename T>
void CArray<T>::Push(const T& item)
{
	if (m_size >= m_capacity)
	{
		Allocate(m_capacity == 0 ? 1 : m_capacity * 2);
	}
	m_data[m_size++] = item;
}

template<typename T>
size_t CArray<T>::Size()
{
	return m_size;
}

template<typename T>
size_t CArray<T>::Capacity()
{
	return m_capacity;
}

template<typename T>
void CArray<T>::Resize(size_t newSize)
{
	if (newSize == m_size)
	{
		return;
	}

	T* newData = new T[newSize];
	try
	{
		std::copy(m_data, m_data + std::min(m_size, newSize), newData); 
	}
	catch (...)
	{
		delete[] newData;
		throw;
	}
	delete[] m_data;

	m_data = newData;
	m_size = newSize;
	m_capacity = newSize;
}

template<typename T>
void CArray<T>::Clear() noexcept
{
	//std destroy_n
	for (size_t i = 0; i < m_size; ++i)
	{
		m_data[i].~T();
	}
	delete[] m_data;

	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template<typename T>
CArray<T>& CArray<T>::operator=(const CArray& other)
{
	if (this != &other) 
	{
		CArray temp(other); 
		Swap(temp);
	}
	return *this;
}

template<typename T>
CArray<T>& CArray<T>::operator=(CArray&& other) noexcept
{
	if (this != &other)
	{
		Clear();

		// Swap or exchange
		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}
	return *this;
}

template <typename T>
T& CArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

template <typename T>
T const& CArray<T>::operator[](size_t index) const
{
	// this->[index]
	return m_data[index];
}

template<typename T>
void CArray<T>::Allocate(size_t size)
{
	T* newData = new T[size];
	try 
	{
		std::copy(m_data, m_data + m_size, newData);
	}
	catch (...) 
	{
		delete[] newData;
		throw;
	}

	delete[] m_data;
	m_data = newData;
	m_capacity = size;
}

template<typename T>
void CArray<T>::Swap(CArray& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T>
template <typename U>
CArray<T>& CArray<T>::operator=(const CArray<U>& other)
{
	CArray temp;
	temp.Resize(other.Size());  

	try 
	{
		for (size_t i = 0; i < other.Size(); ++i) 
		{
			temp.m_data[i] = static_cast<T>(other.m_data[i]); 
		}
	}
	catch (...) 
	{
		temp.Clear();  
		throw;
	}

	Swap(temp);

	return *this;
}
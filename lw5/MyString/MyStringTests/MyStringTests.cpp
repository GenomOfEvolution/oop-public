#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CMyString.h>
#include <sstream>

TEST_CASE("Default constructor")
{
	CMyString str;
	CHECK(str.GetCapacity() == 1);
	CHECK(str.GetLength() == 0);
	CHECK(std::strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("Constructor char*")
{
	CMyString str("Hello");
	CHECK(str.GetLength() == 5);
	CHECK(str.GetCapacity() == 6);
	CHECK(std::strcmp(str.GetStringData(), "Hello") == 0);
}

TEST_CASE("Constructor with length")
{
	CMyString str("SlimShady", 4);
	CHECK(str.GetLength() == 4);
	CHECK(str.GetCapacity() == 5);
	CHECK(std::strcmp(str.GetStringData(), "Slim") == 0);
}

TEST_CASE("Copy constructor")
{
	CMyString str("Hello");
	CMyString copyStr(str);

	CHECK(str.GetLength() == copyStr.GetLength());
	CHECK(str.GetCapacity() == copyStr.GetCapacity());
	CHECK(std::strcmp(str.GetStringData(), copyStr.GetStringData()) == 0);
}

TEST_CASE("Move constructor")
{
	CMyString str("Hello");
	CMyString movedStr(std::move(str));

	CHECK(movedStr.GetLength() == 5);
	CHECK(movedStr.GetCapacity() == 6);
	CHECK(std::strcmp(movedStr.GetStringData(), "Hello") == 0);

	CHECK(str.GetLength() == 0);
	CHECK(str.GetCapacity() == 1);
	CHECK(std::strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("Constructor with std::string")
{
	std::string strSTL = "Hello";
	CMyString str(strSTL);

	CHECK(str.GetLength() == 5);
	CHECK(str.GetCapacity() == 6);
	CHECK(std::strcmp(str.GetStringData(), "Hello") == 0);
}

TEST_CASE("Substring from my string")
{
	CMyString str("SlimShady");
	CMyString copiedPart = str.SubString(4, 5);

	CHECK(copiedPart.GetCapacity() == 5);
	CHECK(copiedPart.GetLength() == 4);
	CHECK(std::strcmp(copiedPart.GetStringData(), "Shad") == 0);

	CHECK_THROWS_AS(copiedPart.SubString(0, 100), std::out_of_range);
}

TEST_CASE("All compare operators")
{
	CMyString str1("aaaaa");
	CMyString str2("bbbbb");
	CMyString str3("aaaaa");

	CHECK(str1 == str1);
	CHECK(str1 == str3);
	CHECK_FALSE(str1 == str2);

	CHECK(str1 != str2);
	CHECK_FALSE(str1 != str3);
	CHECK_FALSE(str2 != str2);

	CHECK(str1 < str2);
	CHECK_FALSE(str1 < str1);
	CHECK_FALSE(str1 < str3);

	CHECK(str1 <= str2);
	CHECK(str1 <= str1);
	CHECK(str1 <= str3);

	CHECK_FALSE(str1 > str2);
	CHECK_FALSE(str1 > str1);
	CHECK_FALSE(str1 > str3);
	CHECK(str2 > str1);

	CHECK_FALSE(str1 >= str2);
	CHECK(str1 >= str1);
	CHECK(str1 >= str3);
	CHECK(str2 >= str1);
}

TEST_CASE("Copying =")
{
	CMyString str1("Hello");
	CMyString str2;

	str2 = str1;
	CHECK(str1.GetCapacity() == 6);
	CHECK(str1.GetLength() == 5);
	CHECK(std::strcmp(str1.GetStringData(), "Hello") == 0);

	CHECK(str2.GetCapacity() == 6);
	CHECK(str2.GetLength() == 5);
	CHECK(std::strcmp(str2.GetStringData(), "Hello") == 0);

	str1 = str1;
	CHECK(str1.GetCapacity() == 6);
	CHECK(str1.GetLength() == 5);
	CHECK(std::strcmp(str1.GetStringData(), "Hello") == 0);
}

// присвоение самого себя
TEST_CASE("Moving =")
{
	CMyString str1("Hello");
	CMyString str2 = std::move(str1);

	CHECK(str1.GetCapacity() == 1);
	CHECK(str1.GetLength() == 0);
	CHECK(std::strcmp(str1.GetStringData(), "") == 0);

	CHECK(str2.GetCapacity() == 6);
	CHECK(str2.GetLength() == 5);
	CHECK(std::strcmp(str2.GetStringData(), "Hello") == 0);
}

TEST_CASE("Operator +")
{
	CMyString str1("Tailer");
	CMyString str2(" Derdan");
	CMyString result;
	result = str1 + str2;
	CHECK(result.GetLength() == 13);
	CHECK(std::strcmp(result.GetStringData(), "Tailer Derdan") == 0);

	result = str1 + std::string(" Derdan");
	CHECK(std::strcmp(result.GetStringData(), "Tailer Derdan") == 0);

	result = str1 + " Derdan";
	CHECK(std::strcmp(result.GetStringData(), "Tailer Derdan") == 0);
}

TEST_CASE("Operator +=")
{
	CMyString str1("Tailer");
	CMyString str2(" Derdan");

	str1 += str2;
	CHECK(str1.GetLength() == 13);
	CHECK(std::strcmp(str1.GetStringData(), "Tailer Derdan") == 0);
}

TEST_CASE("Operator []")
{
	CMyString str("Hello");

	CHECK(str[0] == 'H');
	str[0] = 'a';
	CHECK(str[0] == 'a');

	CHECK_THROWS_AS(str[5], std::out_of_range);
}

TEST_CASE("MyStr with \\0 inside")
{
	const char dataWithZeros[] = {'H', '\0', 'l', 'l', '\0'};
	CMyString str(dataWithZeros, 5);

	CHECK(str.GetLength() == 5);
	CHECK(str.GetCapacity() == 6);
	CHECK(std::strcmp(str.GetStringData(), dataWithZeros) == 0);
}

TEST_CASE("Operators << and >>")
{
	CMyString str("hello");

	std::ostringstream os;
	os << str;
	CHECK(os.str() == "hello");

	std::istringstream is("test");
	CMyString str2;
	is >> str2;
	CHECK(std::strcmp(str2.GetStringData(), "test") == 0);
}

TEST_CASE("Iterators begin, end")
{
	CMyString str("Hello");
	CHECK(str.end() - str.begin() == 5);
	CHECK(std::strcmp(str.begin(), "Hello") == 0);
}

TEST_CASE("Range based for")
{
	CMyString str("Hello");
	std::string expectedResult = "Hello";

	int i = 0;
	for (char ch : str)
	{
		CHECK(ch == expectedResult[i]);
		i++;
	}
}

TEST_CASE("Iterator ++ and --")
{
	CMyString str("Hello");
	auto it = str.begin();
	
	// сравнивать конкретный символ через разыменовывание
	it++;
	CHECK(std::strcmp(it, "ello") == 0);

	it--;
	CHECK(std::strcmp(it, "Hello") == 0);
}

TEST_CASE("Reverse iterator")
{
	CMyString str("Hello");
	std::string expectedResult = "olleH";
	std::string result;
	
	for (auto i = str.rbegin(); i != str.rend(); i++)
	{
		result += *i;
	}

	CHECK(result == expectedResult);
}

// добавить const итераторы
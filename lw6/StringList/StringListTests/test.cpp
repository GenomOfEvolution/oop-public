#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CStringList.h>

namespace
{
	const std::string FIRST_STR = "Hi";
	const std::string SECOND_STR = "My name is";
	const std::string THIRD_STR = "Slim Shady";

	const std::string EXPECTED_ARRAY[] = {FIRST_STR, SECOND_STR, THIRD_STR};
}

TEST_CASE("Default constructor")
{
	CStringList strList;

	CHECK(strList.Size() == 0);
	CHECK(strList.Empty());
}

TEST_CASE("Copy constructor")
{
	CStringList strListFirst;
	strListFirst.PushBack(FIRST_STR);
	strListFirst.PushBack(SECOND_STR);
	strListFirst.PushBack(THIRD_STR);

	CStringList copyTo(strListFirst);
	CHECK(copyTo.Size() == 3);
	auto it = copyTo.begin();
	for (auto i : strListFirst)
	{
		CHECK(*it == i);
		it++;
	}
}

TEST_CASE("Move constructor")
{
	CStringList strListFirst;
	strListFirst.PushBack(FIRST_STR);
	strListFirst.PushBack(SECOND_STR);
	strListFirst.PushBack(THIRD_STR);

	CStringList copyTo(std::move(strListFirst));
	CHECK(strListFirst.Size() == 0);
	CHECK(strListFirst.Empty());

	CHECK(copyTo.Size() == 3);
	int i = 0;
	for (auto it : copyTo)
	{
		CHECK(EXPECTED_ARRAY[i] == it);
		i++;
	}
}

TEST_CASE("Push back")
{
	CStringList strList;
	strList.PushBack(FIRST_STR);
	strList.PushBack(SECOND_STR);
	strList.PushBack(THIRD_STR);

	CHECK(strList.Size() == 3);
	CHECK_FALSE(strList.Empty());

	int i = 0;
	for (auto it : strList)
	{
		CHECK(EXPECTED_ARRAY[i] == it);
		i++;
	}
}

TEST_CASE("Push Front")
{
	CStringList strList;
	strList.PushFront(THIRD_STR);
	strList.PushFront(SECOND_STR);
	strList.PushFront(FIRST_STR);

	CHECK(strList.Size() == 3);
	CHECK_FALSE(strList.Empty());

	int i = 0;
	for (auto it : strList)
	{
		CHECK(EXPECTED_ARRAY[i] == it);
		i++;
	}
}

//TEST_CASE("Insert with iterator")
//{
//	CStringList strList;
//	
//	strList.Insert(strList.begin(), FIRST_STR);
//	auto it = strList.begin();
//	it++;
//	strList.Insert(it, SECOND_STR);
//	it++;
//	strList.Insert(it, THIRD_STR);
//	it--;
//	strList.Insert(it, FIRST_STR);
//
//	CHECK(strList.Size() == 4);
//	const std::string EXPECTED_RESULT[] = { FIRST_STR, SECOND_STR, FIRST_STR, THIRD_STR };
//	int i = 0;
//	for (auto it : strList)
//	{
//		CHECK(it == EXPECTED_RESULT[i]);
//	}
//}

TEST_CASE("Erase with iterator")
{
	CStringList strList;
	strList.PushBack(FIRST_STR);
	strList.PushBack(SECOND_STR);
	strList.PushBack(THIRD_STR);

	auto it = strList
	/*strList.Delete();*/
}
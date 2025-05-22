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
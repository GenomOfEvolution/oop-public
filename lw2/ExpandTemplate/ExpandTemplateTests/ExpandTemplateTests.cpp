#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <ExpandTemplate.h>

TEST_CASE("Basic parameter substitution")
{
	std::map<std::string, std::string> replaceMap = {
		{ "%USER_NAME%", "Ivan Petrov" },
		{ "{WEEK_DAY}", "Friday" }
	};

	const std::string inputStr = "Hello, %USER_NAME%.  \nToday is {WEEK_DAY}.";
	const std::string expectedResult = "Hello, Ivan Petrov.  \nToday is Friday.";

	REQUIRE(ExpandTemplate(inputStr, replaceMap) == expectedResult);
}

TEST_CASE("Template parameter with an empty value")
{
	std::map<std::string, std::string> replaceMap = {
		{ "%USER_NAME%", "" },
		{ "{WEEK_DAY}", "" }
	};

	const std::string inputStr = "Hello, %USER_NAME%.  \nToday is {WEEK_DAY}.";
	const std::string expectedResult = "Hello, .  \nToday is .";

	REQUIRE(ExpandTemplate(inputStr, replaceMap) == expectedResult);
}

TEST_CASE("Substitution with nested parameters")
{
	std::map<std::string, std::string> replaceMap = {
		{ "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" },
		{ "{WEEK_DAY}", "Friday. {WEEK_DAY}" }
	};

	const std::string inputStr = "Hello, %USER_NAME%.  \nToday is {WEEK_DAY}.";
	const std::string expectedResult = "Hello, Super %USER_NAME% {WEEK_DAY}.  \nToday is Friday. {WEEK_DAY}.";

	REQUIRE(ExpandTemplate(inputStr, replaceMap) == expectedResult);
}

TEST_CASE("Selecting the longest match")
{
	std::map<std::string, std::string> replaceMap = {
		{ "A", "[a]" },
		{ "AA", "[aa]" },
		{ "B", "[b]" },
		{ "BB", "[bb]" },
		{ "C", "[c]" },
		{ "CC", "[cc]" }
	};

	const std::string inputStr = "-AABBCCCCCABC+";
	const std::string expectedResult = "-[aa][bb][cc][cc][c][a][b][c]+";

	REQUIRE(ExpandTemplate(inputStr, replaceMap) == expectedResult);
}
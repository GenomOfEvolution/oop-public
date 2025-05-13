#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <FindMaxEx.h>
#include <string>

namespace
{
	struct Athlete
	{
		std::string name;
		double weight = 0;
		double height = 0;
	};

	bool CompareWeight(const Athlete& first, const Athlete& second)
	{
		return first.weight < second.weight;
	}

	bool CompareHeight(const Athlete& first, const Athlete& second)
	{
		return first.height < second.height;
	}

	constexpr int START_VALUE = 42;
	constexpr double MAX_WEIGHT = 100;
	constexpr double MAX_HEIGHT = 192;

	const std::vector<Athlete> athletes = 
	{
		{ "Popov", 60, 176 },
		{ "Ivanov", 77, MAX_HEIGHT },
		{ "Sidorov", MAX_WEIGHT, 173 }
	};
}

TEST_CASE("Empty array")
{
	std::vector<int> arr = {};
	int maxVal;
	CHECK_FALSE(FindMax(arr, maxVal, std::less<int>()));
}

TEST_CASE("All equal elements in array")
{
	const int EQ_VALUE = 5;
	std::vector<int> arr = { EQ_VALUE, EQ_VALUE, EQ_VALUE };
	int maxVal = 0;

	CHECK(FindMax(arr, maxVal, std::less<int>()));
	CHECK(maxVal == EQ_VALUE);
}

TEST_CASE("Single element array")
{
	int maxValue;
	std::vector<int> arr = { START_VALUE };

	CHECK(FindMax(arr, maxValue, std::less<int>()));
	CHECK(maxValue == START_VALUE);
}

TEST_CASE("Commit-or-rollback")
{
	int maxValue = START_VALUE;
	std::vector<int> arr = {};

	CHECK_FALSE(FindMax(arr, maxValue, std::less<int>()));
	CHECK(maxValue == START_VALUE);
}

TEST_CASE("Athlete with max weight")
{
	Athlete maxWeightAthlete;
	CHECK(FindMax(athletes, maxWeightAthlete, CompareWeight));
	CHECK(maxWeightAthlete.weight == MAX_WEIGHT);
}

TEST_CASE("Athlete with max height")
{
	Athlete maxHeightAthlete;
	CHECK(FindMax(athletes, maxHeightAthlete, CompareHeight));
	CHECK(maxHeightAthlete.height == MAX_HEIGHT);
}
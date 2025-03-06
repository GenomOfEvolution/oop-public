#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <PrimesGenerator.h>

TEST_CASE("ѕроверить 0 и 1 - не простые числа")
{
	REQUIRE(GeneratePrimeNumbersSet(1).size() == 0);
}

TEST_CASE("ѕроверить что диапазон работает до границы включительно")
{
	std::set<int> expectedResult = { 2, 3, 5, 7, 11, 13 };

	REQUIRE(GeneratePrimeNumbersSet(13) == expectedResult);
}

// тест граница до не простого числа
TEST_CASE("ѕроверка диапазона включительно, до непростого числа")
{
	std::set<int> expectedResult = { 2, 3, 5, 7, 11 };

	REQUIRE(GeneratePrimeNumbersSet(12) == expectedResult);
}

TEST_CASE("ќтрицательных простых чисел не существует")
{
	REQUIRE(GeneratePrimeNumbersSet(-13).size() == 0);
}

// через define тест только в релизе
#if !defined(_DEBUG)
	TEST_CASE("¬ диапазоне от 1 до 100000000 содержитс€ 5761455 простых чисел")
	{
		REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
	}
#endif


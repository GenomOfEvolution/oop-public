#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <PrimesGenerator.h>

TEST_CASE("Проверить 0 и 1 - не простые числа")
{
	REQUIRE(GeneratePrimeNumbersSet(1).size() == 0);
}

TEST_CASE("Проверить что диапазон работает до границы включительно")
{
	std::set<int> expectedResult = { 2, 3, 5, 7, 11, 13 };

	REQUIRE(GeneratePrimeNumbersSet(13) == expectedResult);
}

TEST_CASE("Отрицательных простых чисел не существует")
{
	REQUIRE(GeneratePrimeNumbersSet(-13).size() == 0);
}

TEST_CASE("В диапазоне от 1 до 100000000 содержится 5761455 простых чисел")
{
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
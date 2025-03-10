#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>
#include <sstream>
#include <VectorProceed.h>

TEST_CASE("Проверить с пустым вектором")
{
	Vector vec = { };
	ProcessNumbers(vec);
	REQUIRE(vec == std::vector<double>{});
}

TEST_CASE("Вектор с одним значением")
{
	Vector vec = { -3 };
	ProcessNumbers(vec);
	REQUIRE(vec == std::vector<double>{9});
}

TEST_CASE("Вектор с дробными значениями")
{
	std::istringstream input("2.0 4 -1.5");
	Vector vec = *ReadNumbers(input);
	REQUIRE(vec == std::vector <double>{2, 4, -1.5});

	ProcessNumbers(vec);
	REQUIRE(vec == std::vector <double>{-3, -6, 2.25});
}

TEST_CASE("Вектор с только положительными значениями")
{
	Vector vec = { 10, 7, 4 };
	ProcessNumbers(vec);
	REQUIRE(vec == std::vector <double>{40, 28, 16});
}

TEST_CASE("Вектор с только отрицательными значениями")
{
	Vector vec = { -1.5, -2, -3 };
	ProcessNumbers(vec);
	REQUIRE(vec == std::vector <double>{4.5, 6, 9});
}

TEST_CASE("Неверные входные данные")
{
	std::istringstream input("abc 2.0 4 -1.5");
	std::optional<Vector> vec = ReadNumbers(input);
	REQUIRE(!vec);
}
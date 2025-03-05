#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <PrimesGenerator.h>

TEST_CASE("��������� 0 � 1 - �� ������� �����")
{
	REQUIRE(GeneratePrimeNumbersSet(1).size() == 0);
}

TEST_CASE("��������� ��� �������� �������� �� ������� ������������")
{
	std::set<int> expectedResult = { 2, 3, 5, 7, 11, 13 };

	REQUIRE(GeneratePrimeNumbersSet(13) == expectedResult);
}

TEST_CASE("������������� ������� ����� �� ����������")
{
	REQUIRE(GeneratePrimeNumbersSet(-13).size() == 0);
}

TEST_CASE("� ��������� �� 1 �� 100000000 ���������� 5761455 ������� �����")
{
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
#include <iostream>
#include "PrimesGenerator.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RU");

    int upperBound = 0;
    std::cout << "������� ������� �������: ";
    std::cin >> upperBound;
    if (std::cin.bad())
    {
        std::cout << "�������� ������ �����\n";
        return EXIT_FAILURE;
    }

    auto primes = GeneratePrimeNumbersSet(upperBound);
    PrintPrimes(std::cout, primes);

    return EXIT_SUCCESS;
}


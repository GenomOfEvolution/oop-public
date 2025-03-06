#include "PrimesGenerator.h"
#include <cmath>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNumbers;
    if (upperBound <= 1)
    {
        return primeNumbers;
    }

    std::vector<bool> allNumbers(upperBound + 1, false);

    // игонорировать все четные числа сразу
    size_t sqrtBound = static_cast<size_t>(std::sqrt(upperBound));
    for (size_t i = 3; i <= sqrtBound; i += 2)
    {
        if (!allNumbers[i])
        {
            for (size_t j = i * i; j <= static_cast<size_t>(upperBound); j += i * 2)
            {
                allNumbers[j] = true;
            }
        }
    }

    primeNumbers.insert(2);

    for (int i = 3; i <= upperBound; i += 2)
    {
        if (!allNumbers[i])
        {
            primeNumbers.insert(i);
        }
    }

    return primeNumbers;
}

void PrintPrimes(std::ostream& output, const std::set<int>& primes)
{
    for (auto i : primes)
    {
        output << i << " ";
    }
}

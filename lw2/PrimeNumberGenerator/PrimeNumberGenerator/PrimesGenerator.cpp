#include "PrimesGenerator.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNumbers;
    if (upperBound <= 1)
    {
        return primeNumbers;
    }

    std::vector<bool> allNumbers(upperBound + 1, true);
    allNumbers[0] = allNumbers[1] = false;

    size_t sqrtBound = static_cast<size_t>(std::sqrt(upperBound));
    for (size_t i = 2; i <= sqrtBound; ++i)
    {
        if (allNumbers[i])
        {
            for (size_t j = i * i; j <= static_cast<size_t>(upperBound); j += i)
            {
                allNumbers[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound; ++i)
    {
        if (allNumbers[i])
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

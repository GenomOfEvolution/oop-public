#pragma once
#include <iostream>
#include <set>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimes(std::ostream& output, const std::set<int>& primes);
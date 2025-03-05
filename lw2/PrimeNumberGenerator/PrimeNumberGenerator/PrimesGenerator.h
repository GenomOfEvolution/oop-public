#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <set>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimes(std::ostream& output, const std::set<int>& primes);
#pragma once
#include <iostream>
#include <vector>
#include <optional>

using Vector = std::vector<double>;

std::optional<Vector> ReadNumbers(std::istream& input);
void ProcessNumbers(Vector& vector);
void PrintSortedNumbers(std::ostream& output, Vector vector);
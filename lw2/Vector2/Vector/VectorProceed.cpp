#include "VectorProceed.h"
#include <algorithm>
#include <iomanip>

std::optional<Vector> ReadNumbers(std::istream& input)
{
	std::vector<double> numbers(std::istream_iterator<double>(input), (std::istream_iterator<double>()));
	if (!input.eof() && input.fail())
	{
		return std::nullopt;
	}

	return numbers;
}

void ProcessNumbers(Vector& vector)
{
	if (!vector.empty())
	{
		double minElement = *std::min_element(vector.begin(), vector.end());
		std::transform(vector.begin(), vector.end(), vector.begin(), [minElement](double num) { return num * minElement; });
	}
}

void PrintSortedNumbers(std::ostream& output, Vector vector)
{
	std::sort(vector.begin(), vector.end());

	output << std::setprecision(3) << std::fixed;
	if (!vector.empty())
	{
		copy(vector.begin(), vector.end() - 1, std::ostream_iterator<double>(output, " "));
		output << *(vector.end() - 1);
	}
	else
	{
		copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	}
}

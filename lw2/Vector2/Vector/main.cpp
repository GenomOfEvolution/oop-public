#include "VectorProceed.h"

int main()
{
    std::optional<Vector> numbers = ReadNumbers(std::cin);
    if (!numbers)
    {
        std::cout << "ERROR";
        return EXIT_FAILURE;
    }

    ProcessNumbers(*numbers);
    PrintSortedNumbers(std::cout, *numbers);

    return EXIT_SUCCESS;
}
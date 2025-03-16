#include "Dictionary.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    WorkWithDictionary(*args);
    return EXIT_SUCCESS;
}
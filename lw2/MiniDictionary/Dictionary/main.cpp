#include "UI.h"
#include <iostream>

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "ru");

    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args) 
    {
        return EXIT_FAILURE;
    }

    RunUI(args->fileName);

    return EXIT_SUCCESS;
}
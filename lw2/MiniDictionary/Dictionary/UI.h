#pragma once
#include <string>
#include <optional>

struct Args 
{
    std::string fileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
void RunUI(const std::string& fileName);
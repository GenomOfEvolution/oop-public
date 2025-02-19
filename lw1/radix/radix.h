#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <algorithm>

const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int FIRST_CHAR_WEIGHT = 10;
const int DEF_ZERO_CHAR = 48;
const int DEF_A_CHAR = 65;
const char MINUS_CHAR = '-';

struct Args
{
	int sourseNotation;
	int destNotation;
	std::string valueString;
};

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);
std::optional<Args> ParseArgs(int argc, char* argv[]);

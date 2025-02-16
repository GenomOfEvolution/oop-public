#include <iostream>
#include <fstream>
#include <optional>
#include <array>
#include <queue>
#include <utility>
#include <string>

const int MAX_FIELD_SIZE = 100;
const char WALL_SYMBOL = '#';
const char FILL_START_SYMBOL = 'O';
const char FILL_SYMBOL = '.';
const char EMPTY_CELL_SYMBOL = ' ';

using Field = std::array<std::array<char, MAX_FIELD_SIZE>, MAX_FIELD_SIZE>;
using FillQueue = std::queue<std::pair<int, int>>;

struct Args
{
	bool IsStdin = false;
	std::string inputFileName;
	std::string outputFileName;
};

void ReadField(std::istream& input, Field& field, FillQueue& fillQueue)
{
	int y = 0;
	std::string line;
	while (std::getline(input, line))
	{
		size_t rightBorder = (line.length() > 100) ? 100 : line.length();
		for (int x = 0; x < rightBorder; x++)
		{
			switch (line[x])
			{
			case WALL_SYMBOL:
				field[y][x] = WALL_SYMBOL;
				break;
			case FILL_START_SYMBOL:
				field[y][x] = FILL_START_SYMBOL;
				fillQueue.push({ y, x });
				break;
			case EMPTY_CELL_SYMBOL:
				field[y][x] = EMPTY_CELL_SYMBOL;
				break;
			default:
				throw std::runtime_error("ERROR");
				break;
			}
		}
		y++;
	}
}

bool CanSpreadFill(int y, int x, const Field& field)
{
	return (y >= 0) && (y <= MAX_FIELD_SIZE) && (x >= 0) && (x <= MAX_FIELD_SIZE) && (field[y][x] == EMPTY_CELL_SYMBOL);
}

void FillField(Field& field, FillQueue& fillQueue)
{
	const std::vector<int> dx = { 0, 0, 1, -1 };
	const std::vector<int> dy = { -1, 1, 0, 0 };
	while (fillQueue.size() > 0)
	{
		std::pair<int, int> curPos = fillQueue.front();
		int x = curPos.first, y = curPos.second;
		fillQueue.pop();
		for (int i = 0; i < dx.size(); i++)
		{
			if (CanSpreadFill(y + dy[i], x + dx[i], field))
			{
				fillQueue.push({ y + dy[i], x + dx[i] });
				field[y][x] = FILL_SYMBOL;
			}
		}
	}
}

std::optional<Args> ParseArgs()
{
	return std::nullopt;
}

void PrintFiled(const Field& filed, std::ostream& output)
{
	for (auto row : filed)
	{
		for (int i = 0; i < row.size(); i++)
		{
			output << row[i];
		}
		output << "\n";
	}
}


int main(int argc, char* argv[])
{
	Field f;
	FillQueue q;

	std::ifstream input;
	input.open(argv[1]);

	if (!input)
	{
		return EXIT_FAILURE;
	}

	try
	{
		ReadField(input, f, q);
	}
	catch (const std::exception&)
	{

	}
	
	FillField(f, q);
	PrintFiled(f, std::cout);

	return EXIT_SUCCESS;
}
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <algorithm>
#include <map>

const size_t MAX_FIELD_SIZE = 100;

enum class CellType
{
    WALL,
    FILL_START,
    FILL,
    EMPTY
};

using Field = std::vector<std::vector<CellType>>;
using FillQueue = std::queue<std::pair<int, int>>;

struct Args
{
    bool isStdin = false;
    std::string inputFileName;
    std::string outputFileName;
};

void ReadField(std::istream& input, Field& field, FillQueue& fillQueue)
{
    std::map<char, CellType> cellTypeMap = {
        {'#', CellType::WALL},
        {'O', CellType::FILL_START},
        {' ', CellType::EMPTY}
    };

    field.resize(MAX_FIELD_SIZE, std::vector<CellType>(MAX_FIELD_SIZE, CellType::EMPTY));

    int y = 0;
    std::string line;
    while (std::getline(input, line) && y < MAX_FIELD_SIZE)
    {
        size_t rightBorder = line.length() > MAX_FIELD_SIZE ? MAX_FIELD_SIZE : line.length();
        for (int x = 0; x < rightBorder; x++)
        {
            char symbol = line[x];
            if (cellTypeMap.find(symbol) != cellTypeMap.end())
            {
                field[y][x] = cellTypeMap[symbol];
                if (symbol == 'O')
                {
                    fillQueue.push({ y, x });
                }
            }
            else
            {
                throw std::runtime_error("ERROR");
            }
        }
        y++;
    }
}

bool CanSpreadFill(int y, int x, const Field& field)
{
    return (y >= 0) && (y < MAX_FIELD_SIZE) && (x >= 0) && (x < MAX_FIELD_SIZE) && (field[y][x] == CellType::EMPTY);
}

void FillField(Field& field, FillQueue& fillQueue)
{
    const std::vector<int> dx = { 0, 0, 1, -1 };
    const std::vector<int> dy = { -1, 1, 0, 0 };
    while (fillQueue.size() > 0)
    {
        std::pair<int, int> curPos = fillQueue.front();
        int y = curPos.first, x = curPos.second;
        fillQueue.pop();
        for (int i = 0; i < dx.size(); i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (CanSpreadFill(newY, newX, field))
            {
                fillQueue.push({ newY, newX });
                field[newY][newX] = CellType::FILL;
            }
        }
    }
}

void PrintField(const Field& field, std::ostream& output)
{
    std::map<CellType, char> cellTypeToChar = {
        {CellType::WALL, '#'},
        {CellType::FILL_START, 'O'},
        {CellType::FILL, '.'},
        {CellType::EMPTY, ' '}
    };

    size_t lastNonEmptyLine = 0;
    size_t firstNonEmptyLine = field.size();

    for (size_t i = 0; i < field.size(); i++)
    {
        const auto& row = field[i];
        auto it = std::find_if(row.begin(), row.end(), [](CellType c) { return c != CellType::EMPTY; });

        if (it != row.end())
        {
            if (firstNonEmptyLine == field.size())
            {
                firstNonEmptyLine = i;
            }
            lastNonEmptyLine = i;
        }
    }

    for (size_t i = firstNonEmptyLine; i <= lastNonEmptyLine; i++)
    {
        const auto& row = field[i];
        size_t lastNonSpace = row.rend() - std::find_if(row.rbegin(), row.rend(), [](CellType c) { return c != CellType::EMPTY; });

        for (size_t j = 0; j < lastNonSpace; j++)
        {
            output << cellTypeToChar[row[j]];
        }

        output << "\n";
    }
}

void PrintHelp()
{
    std::cout << "Usage: \n"
        << "fill.exe <input file> <output file>\n"
        << "Options:\n"
        << "    -h  Show this help message\n"
        << "    If no arguments are provided, input is read from stdin and output is printed to console.\n";
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args result;

    if (argc == 1)
    {
        result.isStdin = true;
        return result;
    }

    if (argc == 2 && argv[1] == "-h")
    {
        PrintHelp();
        return std::nullopt;
    }

    if (argc != 3)
    {
        std::cout << "ERROR";
        return std::nullopt;
    }

    result.inputFileName = argv[1];
    result.outputFileName = argv[2];

    return result;
}

bool Fill(const Args& args)
{
    std::ifstream fileInput;
    std::ofstream fileOutput;

    std::istream& input = args.isStdin ? std::cin : fileInput;
    std::ostream& output = args.isStdin ? std::cout : fileOutput;

    if (!args.isStdin)
    {
        fileInput.open(args.inputFileName);
        if (!fileInput)
        {
            return EXIT_FAILURE;
        }

        fileOutput.open(args.outputFileName, std::ios::trunc);
        if (!fileOutput)
        {
            return EXIT_FAILURE;
        }
    }

    Field field;
    FillQueue fillQueue;

    try
    {
        ReadField(input, field, fillQueue);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what();
        return EXIT_FAILURE;
    }

    FillField(field, fillQueue);
    PrintField(field, output);

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);

    if (!args)
    {
        return (argc == 1) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    bool exitResult = Fill(*args);

    return exitResult;
}
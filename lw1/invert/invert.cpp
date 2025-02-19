#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <array>
#include <iomanip>
#include <sstream>

const size_t MATRIX_SIZE = 3;
using Matrix3x3d = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    bool isStdin = false;
};

Matrix3x3d ReadMatrix(std::istream& input)
{
    Matrix3x3d matrix;
    std::string line;
    size_t row = 0;

    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        size_t col = 0;
        double value;

        while (iss >> value)
        {
            if (col < MATRIX_SIZE && row < MATRIX_SIZE)
            {
                matrix[row][col] = value;
            }
            
            col++;
        }

        if (iss.fail() && !iss.eof())
        {
            throw std::runtime_error("Invalid matrix");
        }

        if (col != MATRIX_SIZE)
        {
            throw std::runtime_error("Invalid matrix format");
        }

        row++;
    }

    if (row != MATRIX_SIZE)
    {
        throw std::runtime_error("Invalid matrix format");
    }

    return matrix;
}

void PrintMatrix(std::ostream& output, const Matrix3x3d& matrix)
{
    output << std::fixed << std::setprecision(3);
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            output << matrix[i][j];
            if (j < MATRIX_SIZE - 1)
            {
                output << "\t";
            }
        }
        output << std::endl;
    }
}

double CalcDeterminant(const Matrix3x3d& matrix)
{
    double det = 0;
    det += matrix[0][0] * matrix[1][1] * matrix[2][2];
    det += matrix[0][1] * matrix[1][2] * matrix[2][0];
    det += matrix[0][2] * matrix[1][0] * matrix[2][1];

    det -= matrix[0][2] * matrix[1][1] * matrix[2][0];
    det -= matrix[0][1] * matrix[1][0] * matrix[2][2];
    det -= matrix[0][0] * matrix[1][2] * matrix[2][1];
    return det;
}

Matrix3x3d InvertMatrix(const Matrix3x3d& matrix)
{
    double det = CalcDeterminant(matrix);
    if (det == 0)
    {
        throw std::runtime_error("Non-invertible");
    }

    Matrix3x3d inverted;
    inverted[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) / det;
    inverted[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / det;
    inverted[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / det;

    inverted[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / det;
    inverted[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / det;
    inverted[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) / det;

    inverted[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) / det;
    inverted[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) / det;
    inverted[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / det;

    return inverted;
}

bool Invert(const Args& args)
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

    Matrix3x3d matrix;
    Matrix3x3d inverted;
    try
    {
        matrix = ReadMatrix(input);
        inverted = InvertMatrix(matrix);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    PrintMatrix(output, inverted);

    return EXIT_SUCCESS;
}

void PrintHelp()
{
    std::cout << "Usage: invert.exe <input> <output> \n" 
     << "  -h: Show this help message \n"
     << "  input: File or stdin containing a 3x3 matrix \n";
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args result;
    if (argc == 1)
    {
        result.isStdin = true;
        return result;
    }

    if (argc == 2 && std::string(argv[1]) == "-h")
    {
        PrintHelp();
        return std::nullopt;
    }

    if (argc != 3)
    {
        return std::nullopt;
    }

    result.inputFileName = argv[1];
    result.outputFileName = argv[2];

    return result;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        return (argc == 1) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    bool exitResult = Invert(*args);

    return exitResult;
}
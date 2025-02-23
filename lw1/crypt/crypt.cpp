#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <optional>

struct Args
{
    bool isCrypt = false;
    uint8_t key = 0;
    std::string inputFileName;
    std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }

    if (std::strcmp(argv[1], "crypt") != 0 && std::strcmp(argv[1], "decrypt") != 0)
    {
        return std::nullopt;
    }

    Args result;
    result.isCrypt = (std::strcmp(argv[1], "crypt")) == 0;
    result.inputFileName = argv[2];
    result.outputFileName = argv[3];

    int key = std::stoi(argv[4]);
    if (key > UINT8_MAX || key < 0)
    {
        std::cout << "Key must be between 0 and 255\n";
        return std::nullopt;
    }
    result.key = static_cast<uint8_t>(key);

    return result;
}

char CryptByte(const char byte, uint8_t key)
{
    uint8_t xorByte = byte ^ key;
    uint8_t result = 0;

    result |= (xorByte << 2) & 0b00011100;
    result |= (xorByte >> 5) & 0b00000011;
    result |= (xorByte >> 2) & 0b00100000;
    result |= (xorByte << 3) & 0b11000000;

    return result;
}

char DecryptByte(const char byte, uint8_t key)
{
    uint8_t result = 0;

    result |= (byte >> 2) & 0b00000111;
    result |= (byte << 5) & 0b01100000;
    result |= (byte << 2) & 0b10000000;
    result |= (byte >> 3) & 0b00011000;

    return result ^ key;
}

bool CryptDecrypt(const Args& args)
{
    std::ifstream input(args.inputFileName, std::ios::binary);
    if (!input) 
    {
        std::cout << "Error opening input file: " << args.inputFileName << "\n";
        return EXIT_FAILURE;
    }

    std::ofstream output(args.outputFileName, std::ios::binary);
    if (!output) 
    {
        std::cout << "Error opening output file: " << args.outputFileName << "\n";
        return EXIT_FAILURE;
    }

    char byte;
    while (input.get(byte)) 
    {
        char processedByte = args.isCrypt ? CryptByte(byte, args.key) : DecryptByte(byte, args.key);
        output.put(processedByte);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Use: crypt.exe <crypt/decrypt> <input> <output> <key>\n";
        return EXIT_FAILURE;
    }

    bool exitResult = CryptDecrypt(*args);

    return exitResult;
}
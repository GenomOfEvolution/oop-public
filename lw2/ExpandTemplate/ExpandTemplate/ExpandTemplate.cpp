#include "Trie.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Trie trie;

    trie.Insert("his");
    trie.Insert("her");
    trie.Insert("hers");
    trie.Insert("she");

    trie.BuildSuffixLinks();

    std::cout << "Words added successfully!" << std::endl;

    return EXIT_SUCCESS;
}
#include "WordNet.h"
#include <iostream>

int main() {
    psv::WordNet tree;
    tree.insert("hello");
    tree.insert("wod");
    tree.insert("hello");
    tree.insert("world");
    tree.insert("per");
    tree.insert("pfter");
    tree.insert("supercalifragilisticexpialidocious");

    std::map<std::string, int> wordCounts = tree.getCounts();

    for (auto& word : wordCounts) {
        std::cout << word.first << " " << word.second << std::endl;
    }

    std::cout << "Total words: " << tree.getTotalWords() << std::endl;
    std::cout << "Unique words: " << tree.getUniqueWords() << std::endl;
    std::cout << "Long unique words: " << tree.getLongUnique() << std::endl;
    std::cout << "Average word length: " << tree.getAverageWordLength() << std::endl;


    return 0;
}

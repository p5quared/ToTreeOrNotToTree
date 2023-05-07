#include "FileHandle.h"
#include "WordNet.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

void clearPunctuation(std::string& sentence){
    if(sentence.empty()){
        return;
    }
    sentence = std::regex_replace(sentence, std::regex("[^a-zA-Z \n]"), "");

//    sentence.erase(std::remove_if (sentence.begin (), sentence.end (), ispunct), sentence.end ());
}


int main(int argc, char **argv){
    if(argc < 2 || argc > 3){
        std::cout << "Usage: ./cleanup <input>" << std::endl;
        std::cout << "Or: ./cleanup <input> <output>" << std::endl;
        return 1;
    }

    std::ifstream ifile(argv[1]);
    if(!ifile){
        std::cout << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }


    std::ofstream ofile;
    if (argc == 3){
        ofile.open(argv[2]);
    }else{
        ofile.open("output.txt");
    }

    std::string sentence;
    psv::WordNet wordNet;
    while(std::getline(ifile, sentence, '.')){
        clearPunctuation(sentence);

        std::string word;
        std::stringstream ss(sentence);
        while(ss >> word){
            wordNet.insert(word);
        }

        wordNet._sentences++;
    }
//    Console Printing
//    wordNet.print();
//    std::cout << "Total words: " << wordNet.getTotalWords() << std::endl;
//    std::cout << "Unique words: " << wordNet.getUniqueWordCount() << std::endl;
//    std::cout << "Long unique words: " << wordNet.getLongUniqueCount() << std::endl;
//    std::cout << "Average word length: " << wordNet.getAverageWordLength() << std::endl;
//    std::cout << "Average sentence length: " << wordNet.getTotalWords() / wordNet._sentences << std::endl;
//    for(auto& word: wordNet.overusedWords()){
//        std::cout << word << std::endl;
//    }

    // get just the name of the file, no extension
    std::string filename = argv[1];
    filename = filename.substr(0, filename.find_last_of('.'));
    filename = filename.substr(filename.find_last_of('/') + 1);
    std::cout << filename;

    psv::saveReport(filename, wordNet);
    psv::saveReportHTML(filename, wordNet);
    psv::saveReportPDF(filename);

    return 0;
}
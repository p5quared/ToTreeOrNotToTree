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
}


int main(int argc, char **argv){
    if(argc != 2){
        std::cout << "Usage: ./cleanup <input>" << std::endl;
        return 1;
    }

    std::ifstream ifile(argv[1]);
    if(!ifile){
        std::cout << "Could not open file: " << argv[1] << std::endl;
        return 1;
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
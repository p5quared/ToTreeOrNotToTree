#include "WordNet.h"

#include <string>
#include <iostream>
#include <fstream>

#ifndef O_DIR
#define O_DIR ""
#endif
namespace psv
{
void saveReport(const std::string& filename, const WordNet& wordnet){
    /*
     * Data in Report:
     * 1. Total Words
     * 2. Unique Words
     * 3. Long Unique Words
     * 4. Average Word Length
     * 5. Word Counts
     * 6. Average Sentence Length
     */
    std::ofstream ofile;
    ofile.open(O_DIR + filename);

    ofile << "Text-Report!!!!!" << std::endl;
    ofile << "Total Words: " << wordnet.getTotalWords() << std::endl;
    ofile << "Unique Words: " << wordnet.getUniqueWordCount() << std::endl;
    ofile << "Long Unique Words: " << wordnet.getLongUniqueCount() << std::endl;
    ofile << "Average Word Length: " << wordnet.getAverageWordLength() << std::endl;
    ofile << "Average Sentence Length: " << wordnet.averageSentenceLength() << std::endl << std::endl;
    if (wordnet.warnSentenceLength())
        ofile << "WARNING: Average Sentence Length is greater than 10 words" << std::endl;
    else
        ofile << "OKAY: Average Sentence Length is less than 10 words" << std::endl;

    if (wordnet.warnWordLength())
        ofile << "WARNING: Average Word Length is greater than 5 characters\n\n" << std::endl;
    else
        ofile << "OKAY: Average Word Length is less than 5 characters\n\n";

    ofile << "Overused Words: " << std::endl;
    for (auto& word: wordnet.warnOverUsed()){
        ofile << word << std::endl;
    }
    // Print Index of Words
    ofile << "Index of Words: " << std::endl;
    char letter = 'A';
    bool first = true;
    for (const auto& word : wordnet){
        if (word._data[0] != letter || first){
            first = false;
            letter = word._data[0];
            ofile << std::endl;
            ofile << "--" << letter << static_cast<char>(tolower(letter)) << "--";
            ofile << std::endl;
        }
        ofile <<  word._data  << std::endl;
    }
}
void saveReportHTML(const std::string& filename, const WordNet& wordnet){

    std::ofstream ofile;
    ofile.open(O_DIR + filename);
    ofile << "Overused Words: " << std::endl;
    for (auto& word: wordnet.warnOverUsed()){
        ofile << word << std::endl;
    }
    // Print Index of Words
    ofile << "Index of Words: " << std::endl;
    char letter = 'A';
    bool first = true;
    ofile << "<ol>" << std::endl;
    for (const auto& word : wordnet){
        if (word._data[0] != letter || first){
            first = false;
            letter = word._data[0];
            ofile << std::endl;
            ofile << "<h1>" << letter << static_cast<char>(tolower(letter))<< "</h1>";
            ofile << std::endl;
        }
        ofile << "<li>" << word._data <<"</li>" << std::endl;
    }
    ofile << "</ol>" << std::endl;
}
//TODO: saveReportHTML
//TODO: saveReportPDF
}
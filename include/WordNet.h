#pragma once

#include "Tree.h"
#include <string>
#include <map>
#include <utility>
#include <vector>

namespace psv
{


static const int LONG_WORD_LENGTH = 3;
static const double WORD_USAGE_WARNING_PERCENT = 0.05;


class WordNet : public Tree<std::string> {
public:
    WordNet() : _long(), _unique_words(), _long_unique(), _total_words(), _total_characters(), _sentences() {}
    // Access
    std::map<std::string, int> getCounts() const;
    int getUniqueWordCount() const { return _unique_words; }
    int getLongUniqueCount() const { return _long_unique; } // #words with length > LONG_WORD_LENGTH (3)
    unsigned int getAverageWordLength() const { return _total_characters / _total_words; }
    unsigned int getTotalWords() const { return _total_words; };
    unsigned int averageSentenceLength() const { return _total_words / _sentences; }
    bool warnSentenceLength() const {return this->averageSentenceLength() > 10;} // warning for average sentence length > 10 words
    bool warnWordLength() const {return this->getAverageWordLength() > 5;}
    bool warnOverused() const {return this->overusedWords().size();}
    std::vector<std::string> overusedWords() const;
    // TODO: Move construction from file into class so we can make this private
    int _sentences;

private:
    int _long;
    int _unique_words;
    int _long_unique;
    unsigned int _total_words;
    unsigned int _total_characters;
    std::map<std::string, int> _getCounts(Node<std::string> *node) const;
    void _insert(Node<std::string> *&node, Node<std::string> *parent, const std::string &data) override;
};


}


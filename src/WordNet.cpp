#include <iostream>
#include "WordNet.h"

namespace psv
{


void WordNet::_insert(Node<std::string> *&node, Node<std::string> *parent, const std::string &data) {
    if (node == nullptr) { // new word
        node = new Node(data);
        node->_parent = parent;
        _unique_words++;
        _total_words++;
        _total_characters += data.length();
        if (data.length() > LONG_WORD_LENGTH){
            _long_unique++;
            _long++;
        }
        return;
    }
    if (node->_data == data) { // existing word
        node->_count++;
        _total_words++;
        _total_characters += data.length();
        if (data.length() > LONG_WORD_LENGTH)
            _long++;

        return;
    }
    if (node->_data > data) {
        _insert(node->_left,node, data);
    } else {
        _insert(node->_right,node, data);
    }
}

/**
 * @brief Returns a map of words and their counts
 *
 * @return std::map<std::string, int> Map of words and their counts
 */
std::map<std::string, int> WordNet::getCounts() const {
    return _getCounts(_root);
}
// Inner recursive call for getCounts
std::map<std::string, int> WordNet::_getCounts(Node<std::string> *node) const {
    if (node == nullptr) {
        return {};
    }
    std::map<std::string, int> left = _getCounts(node->_left);
    std::map<std::string, int> right = _getCounts(node->_right);
    std::map<std::string, int> result;
    for (auto &[word, count]: left) {
        result[word] = count;
    }
    for (auto &[word, count]: right) {
        result[word] = count;
    }
    result[node->_data] = node->_count;
    return result;
}

/**
 * @brief Returns a vector of words that are used more than WORD_USAGE_WARNING_PERCENT of the total words
 *
 * @return std::vector<std::string> Vector of overused words
 */
std::vector<std::string> WordNet::overusedWords() const {
    const auto wordCounts = this->getCounts();
    std::vector<std::string> overused;

    for(const auto& [word, count] : wordCounts){
        if(word.length() <= LONG_WORD_LENGTH)
            continue;
        if(count > WORD_USAGE_WARNING_PERCENT * _long_unique){
            overused.push_back(word);
        }
    }
    return overused;
}


} // namespace psv
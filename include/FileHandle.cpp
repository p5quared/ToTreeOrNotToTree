#include "WordNet.h"
#include "ctml.h"

#include <curl/curl.h>
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
    ofile.open(O_DIR + filename + "_report.txt");

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
    for (auto& word: wordnet.overusedWords()){
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
/**
 * @brief Saves the report in HTML format by generating nodes and placing them into a template file.
 * @param filename Name of output file (default directory is data/output)
 * @param wordnet The wordnet to save
 *
 */
void saveReportHTML(const std::string& filename, const WordNet& wordnet){
    CTML::Node total_words_td("td", std::to_string(wordnet.getTotalWords()));
    CTML::Node unique_words_td("td", std::to_string(wordnet.getUniqueWordCount()));
    CTML::Node long_unique_words_td("td", std::to_string(wordnet.getLongUniqueCount()));
    CTML::Node average_word_length_td("td", std::to_string(wordnet.getAverageWordLength()));
    CTML::Node average_sentence_length_td("td", std::to_string(wordnet.averageSentenceLength()));

    CTML::Node warn_sentence_length_p;
    CTML::Node warn_word_length_p;
    CTML::Node warn_overused_p;
    std::vector<CTML::Node> overused_words_p;
    if(wordnet.warnSentenceLength())
        warn_sentence_length_p = CTML::Node("p.warning", "WARNING: Average Sentence Length is greater than 10 words");
    else
        warn_sentence_length_p = CTML::Node("p.nowarn", "OKAY: Average Sentence Length is less than 10 words");
    if(wordnet.warnWordLength())
        warn_word_length_p = CTML::Node("p.warning", "WARNING: Average Word Length is greater than 5 characters");
    else
        warn_word_length_p = CTML::Node("p.nowarn", "OKAY: Average Word Length is less than 5 characters");
    if(wordnet.warnOverused()){
        warn_overused_p = CTML::Node("p.warning", "WARNING: The following words may be overused: ");
        std::vector<std::string> overused = wordnet.overusedWords();
        overused_words_p.reserve(overused.size());
        for (auto& word : overused){
            overused_words_p.emplace_back("p.overusedWords", word);
        }
    }else{
        warn_overused_p = CTML::Node("p.nowarn", "OKAY: No overused words detected.");
    }

    std::string total_words_str = total_words_td.ToString();
    std::string unique_words_str = unique_words_td.ToString();
    std::string long_unique_words_str = long_unique_words_td.ToString();
    std::string average_word_length_str = average_word_length_td.ToString();
    std::string average_sentence_length_str = average_sentence_length_td.ToString();

    std::string warn_sentence_length_str = warn_sentence_length_p.ToString();
    std::string warn_word_length_str = warn_word_length_p.ToString();
    std::string warn_overused_str = warn_overused_p.ToString();
    std::vector<std::string> overused_words_str;
    overused_words_str.reserve(overused_words_p.size());
for (auto& word : overused_words_p){
        overused_words_str.push_back(word.ToString());
    }

    // Insert into HTML Template
    std::ifstream html_template("../lib/template.html");
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(html_template, line)){
        if(line == "<!-- insert total number of words here -->"){
//            std::cout << total_words_str << std::endl;
            lines.push_back(total_words_str);
        }
        else if(line == "<!-- insert number of unique words here -->"){
//            std::cout << unique_words_str << std::endl;
            lines.push_back(unique_words_str);
        }
        else if (line == "<!-- insert number of unique words of more than three letters here -->"){
//            std::cout << long_unique_words_str << std::endl;
            lines.push_back(long_unique_words_str);
        }
        else if (line == "<!-- insert average word length here -->"){
//            std::cout << average_word_length_str << std::endl;
            lines.push_back(average_word_length_str);
        }
        else if (line == "<!-- insert average sentence length here -->"){
//            std::cout << average_sentence_length_str << std::endl;
            lines.push_back(average_sentence_length_str);
        }
        else if(line == "<!-- insert warning messages here (if applicable) -->"){
//            std::cout << warn_sentence_length_str << std::endl;
            lines.push_back(warn_sentence_length_str);
//            std::cout << warn_word_length_str << std::endl;
            lines.push_back(warn_word_length_str);
//            std::cout << warn_overused_str << std::endl;
            lines.push_back(warn_overused_str);
            for (auto& word : overused_words_str){
//                std::cout << word << std::endl;
                lines.push_back(word);
            }
        }
        else if(line == "<!-- insert index (alphabetical listing) of all the unique words here -->"){
//            std::cout << "Found Index location" << std::endl;
            char letter = 'A';
            bool first = true;
            for (const auto& word : wordnet){
                if (word._data[0] != letter || first){
                    first = false;
                    letter = word._data[0];
//                    std::cout << "<h1>" << letter << "</h1>" << std::endl;
                    lines.push_back("<h1>" + std::string(1, letter) + static_cast<char>(tolower(letter)) + "</h1>");
                }
//                std::cout << "<p>" << word._data << "</p>" << std::endl;
                lines.push_back("<p>" + word._data + "</p>");
            }
        }
        else {
//            std::cout << line << std::endl;
            lines.push_back(line);
        }

        std::ofstream ofile(O_DIR + filename + "_report.html");
        for (auto& line : lines){
            ofile << line << std::endl;
        }
        ofile.close();
    }
}
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/**
 * @brief Saves a report of the wordnet (*.html) to a PDF file
 * @brief via wkhtmltopdf running on a server I made because I couldn't get it to work locally...ugh????
 * @param filename Name of output file (default directory is data/output)
 * @param wordnet The wordnet to save
 *
 */
void saveReportPDF(const std::string& filename){
    FILE *fileUpload = fopen((O_DIR + filename + "_report.html").c_str(), "rb");
    std::cout << "Opening file: " << O_DIR + filename + "_report.html" << std::endl;
    if(!fileUpload) {
        std::cout << "Error: Unable to open file for PDF conversion: " << filename << ".html";
        exit(1);
    }

    // This section mostly is from https://curl.se/libcurl/c/fileupload.html and similar
    // and I feel scarred for life after reading it
    CURL *curl = curl_easy_init();
    if(!curl) {
        std::cout << "Error: Unable to initialize curl for PDF conversion: " << filename << ".html";
        exit(1);
    }

    // Curl mime
    curl_mime *form_mime = curl_mime_init(curl);
    curl_mimepart *field = curl_mime_addpart(form_mime);
    curl_mime_name(field, "file");
    curl_mime_filedata(field, (O_DIR + filename + "_report.html").c_str());

    field = curl_mime_addpart(form_mime);
    curl_mime_name(field, "file");
    curl_mime_data(field, filename.c_str(), CURL_ZERO_TERMINATED);
    struct curl_slist *headerlist = curl_slist_append(headerlist, "Expect:");

    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form_mime);

    // Upload Settings:
    curl_easy_setopt(curl, CURLOPT_URL, "https://htmltopdf.fly.dev/api");

    // Download Settings:
    std::string outfile_name = O_DIR + filename + "_report.pdf";
    FILE *fileDownload = fopen(outfile_name.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fileDownload);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);

    // Perform request
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    // Cleanup
    curl_easy_cleanup(curl);
    fclose(fileUpload);
    fclose(fileDownload);
}
}
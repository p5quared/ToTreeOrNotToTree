//
// Created by Peter Vaiciulis on 5/5/23.
//
#pragma once
#include "WordNet.h"

#include <string>

namespace psv
{
    void saveReport(const std::string& filename, const WordNet& wordnet);
    void saveReportPDF(const std::string& filename, const WordNet& wordnet);
}

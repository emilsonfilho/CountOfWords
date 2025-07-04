#ifndef WORD_FREQUENCY_ANALYZER_HPP
#define WORD_FREQUENCY_ANALYZER_HPP

#include <memory>

#include "Dictionary/IDictionary.hpp"
#include "Reports/ReportData.hpp"

class WordFrequencyAnalyzer {
public:
    ReportData analyze(
        std::unique_ptr<IDictionary<std::string, int>> dictionary,
        const vector<std::string>& words
    ) const;
};

#endif
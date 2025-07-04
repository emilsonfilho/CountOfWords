#ifndef REPORT_DATA_HPP
#define REPORT_DATA_HPP

#include <string>
#include <chrono>

struct ReportData {
    std::string dictionaryType;
    std::chrono::milliseconds buildTime;
    size_t comparisons;
    std::pair<std::string, size_t> specificMetric;
    size_t totalWordsProcessed;    
};

#endif
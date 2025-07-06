#ifndef REPORT_WRITER_HPP
#define REPORT_WRITER_HPP

#include <iostream>
#include <memory>

#include "ReportData.hpp"
#include "Dictionary/IDictionary.hpp"

class ReportWriter {
    void printLine(std::ostream& out) const;
    void printHeader(const std::string& title, std::ostream& out) const;
public:
    void exportReport(const ReportData& reportData, std::ostream& out, IDictionary<std::string, int>* dict);
};

#endif
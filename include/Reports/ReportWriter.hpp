#ifndef REPORT_WRITER_HPP
#define REPORT_WRITER_HPP

#include <iostream>
#include <memory>

#include "ReportData.hpp"
#include "Dictionary/IDictionary.hpp"

class ReportWriter {
    void printLine(std::ostream&) const;
public:
    void exportReport(const ReportData& reportData, std::ostream& out, std::unique_ptr<IDictionary<std::string, int>> dict);
};

#endif
#ifndef REPORT_WRITER_HPP
#define REPORT_WRITER_HPP

#include <iostream>
#include <memory>

#include "Dictionary/IDictionary.hpp"
#include "ReportData.hpp"

class ReportWriter {
  static void printLine(std::ostream &out);
  static void printHeader(const std::string &title, std::ostream &out);

public:
  static void exportReport(const ReportData &reportData, std::ostream &out,
                           IDictionary<std::string, size_t> *dict);
};

#endif
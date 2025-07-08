#ifndef REPORT_WRITER_HPP
#define REPORT_WRITER_HPP

#include <iostream>
#include <memory>

#include "Dictionary/IDictionary.hpp"
#include "ReportData.hpp"
#include "LexicalStr/LexicalStr.hpp"

/**
 * @class ReportWriter
 * @brief Provides static methods to format and export dictionary reports.
 *
 * This class handles the formatting and printing of dictionary data to an output stream.
 * It includes methods for printing headers, separators, and exporting the full report
 * using provided dictionary data and metadata.
 */
class ReportWriter {
  /**
   * @brief Prints a horizontal line separator to the output stream.
   *
   * Useful for visually separating sections of the report.
   *
   * @param out The output stream to write to.
   */
  static void printLine(std::ostream &out);

  /**
   * @brief Prints a formatted report header with a given title.
   *
   * @param title The title to display at the top of the report.
   * @param out The output stream to write the header to.
   */
  static void printHeader(const std::string &title, std::ostream &out);

public:
  /**
   * @brief Exports the full dictionary report to the given output stream.
   *
   * This method uses metadata and dictionary contents to generate a structured
   * report. It is responsible for formatting keys and their frequencies.
   *
   * @param reportData Metadata about the report formatting and context.
   * @param out The output stream where the report will be written.
   * @param dict Pointer to the dictionary containing key-frequency pairs.
   */
  static void exportReport(const ReportData &reportData, std::ostream &out,
                           IDictionary<LexicalStr, size_t> *dict);
};


#endif
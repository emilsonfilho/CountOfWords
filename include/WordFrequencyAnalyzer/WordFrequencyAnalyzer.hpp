#ifndef WORD_FREQUENCY_ANALYZER_HPP
#define WORD_FREQUENCY_ANALYZER_HPP

#include <memory>
#include <vector>

#include "Dictionary/IDictionary.hpp"
#include "FileProcessor/FileProcessor.hpp"
#include "Reports/ReportData.hpp"
#include "LexicalStr/LexicalStr.hpp"

class WordFrequencyAnalyzer {
public:
  /**
   * @brief Analyzes the frequency of words in the provided list and generates a
   * report.
   *
   * This function processes the given vector of words, counts their occurrences
   * using the provided dictionary, and returns a report containing the
   * frequency analysis results.
   *
   * @param dictionary A unique pointer to an IDictionary instance used to store
   * and count word frequencies.
   * @param words A constant reference to a vector of strings representing the
   * words to be analyzed.
   * @return ReportData An object containing the results of the word frequency
   * analysis.
   */
  static ReportData analyze(IDictionary<LexicalStr, size_t> *dictionary,
                            const FileProcessor &fileProcessor);
};

#endif
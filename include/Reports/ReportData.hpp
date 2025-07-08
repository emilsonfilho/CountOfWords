#ifndef REPORT_DATA_HPP
#define REPORT_DATA_HPP

#include <chrono>
#include <string>

/**
 * @struct ReportData
 * @brief Aggregates performance metrics and metadata for reporting on
 * dictionary data structures.
 *
 * This structure is used to consolidate various statistics collected from a
 * dictionary implementation during benchmarking or analysis. It holds
 * information about the structure's type, build time, comparison counts, and
 * other relevant metrics.
 */
struct ReportData {
  /**
   * @brief The name of the dictionary implementation being reported on.
   * @details Example: "AVLTree", "RedBlackTree", "ChainedHashTable".
   */
  std::string dictionaryType;

  /**
   * @brief The total time taken to build or populate the data structure, in
   * milliseconds.
   */
  std::chrono::milliseconds buildTime;

  /**
   * @brief The total number of key comparisons performed during a benchmarked
   * operation.
   */
  size_t comparisons;

  /**
   * @brief A metric specific to a particular dictionary type.
   * @details For example, for a hash table, this stores the number of
   * collisions. The `first` element of the pair is the metric's name (e.g.,
   * "Max Collisions"), and the `second` element is its value.
   */
  std::pair<std::string, size_t> specificMetric;

  /**
   * @brief The total number of words or items processed during the test run.
   */
  size_t totalWordsProcessed;

  /**
   * @brief Name of the file associated with the report.
   *
   * Used to display or log which input file generated this data.
   */
  std::string filename;

  /**
   * @brief Length of the longest key stored in the dictionary.
   *
   * Useful for aligning columns or formatting output.
   */
  size_t maxKeyLength;
};

#endif
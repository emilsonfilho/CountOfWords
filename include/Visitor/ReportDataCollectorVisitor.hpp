#ifndef REPORT_DATA_VISITOR_HPP
#define REPORT_DATA_VISITOR_HPP

#include <functional>

#include "Dictionary/IDictionary.hpp"
#include "Reports/ReportData.hpp"
#include "Visitor/IDictionaryVisitor.hpp"

/**
 * @class ReportDataCollectorVisitor
 * @brief Implements the visitor pattern to collect performance metrics from
 * various dictionary data structures.
 *
 * This class visits different dictionary implementations (like AVL Trees,
 * Red-Black Trees, and Hash Tables), extracts relevant metrics such as
 * comparison counts, and populates a ReportData object.
 *
 * @tparam Key The key type of the elements in the dictionary.
 * @tparam Value The value type of the elements in the dictionary.
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Compare = std::less<Key>>
class ReportDataCollectorVisitor : public IDictionaryVisitor<Key, Value> {
  /**
   * @var report
   * @brief A reference to the ReportData object where collected metrics will be
   * stored.
   */
  ReportData &report;

  /**
   * @brief Extracts the total number of comparisons from a dictionary and adds
   * it to the report.
   * @param dict The dictionary from which to retrieve the comparison count.
   */
  void addComparisonsCount(const IDictionary<Key, Value> &dict);

  /**
   * @brief Sets the type name of the dictionary being processed in the report.
   * @param dictType A string representing the dictionary's type (e.g., "AVL
   * Tree").
   */
  void setDictionaryType(const std::string &dictType);

public:
  /**
   * @brief Constructs a ReportDataCollectorVisitor.
   * @param data A reference to the ReportData object that will be populated
   * with metrics.
   */
  ReportDataCollectorVisitor(ReportData &data);

  /**
   * @brief Collects performance metrics from an AVLTree.
   *
   * This method sets the dictionary type to "AVLTree" and records its
   * comparison count in the ReportData object provided during construction.
   *
   * @param avlTree The AVLTree instance to be analyzed.
   */
  void collectMetrics(const AVLTree<Key, Value, Compare> &avlTree);

  /**
   * @brief Collects performance metrics from a RedBlackTree.
   *
   * This method sets the dictionary type to "RedBlackTree" and records its
   * comparison count in the ReportData object provided during construction.
   *
   * @param redBlackTree The RedBlackTree instance to be analyzed.
   */
  void collectMetrics(const RedBlackTree<Key, Value, Compare> &redBlackTree);

  /**
   * @brief Collects performance metrics from a ChainedHashTable.
   *
   * This method sets the dictionary type to "ChainedHashTable" and records its
   * comparison count in the ReportData object provided during construction.
   *
   * @param chainedHashTable The ChainedHashTable instance to be analyzed.
   */
  void
  collectMetrics(const ChainedHashTable<Key, Value, Hash> &chainedHashTable);

  /**
   * @brief Collects performance metrics from an OpenAddressingHashTable.
   *
   * This method sets the dictionary type to "OpenAddressingHashTable" and
   * records its comparison count in the ReportData object provided during
   * construction.
   *
   * @param openAddressingHashTable The OpenAddressingHashTable instance to be
   * analyzed.
   */
  void collectMetrics(
      const OpenAddressingHashTable<Key, Value, Hash> &openAddressingHashTable);
};

#include "Visitor/ReportDataCollectorVisitor.impl.hpp"

#endif
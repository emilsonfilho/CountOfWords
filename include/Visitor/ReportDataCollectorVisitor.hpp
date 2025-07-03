#ifndef REPORT_DATA_VISITOR_HPP
#define REPORT_DATA_VISITOR_HPP

#include <functional>

#include "Dictionary/IDictionary.hpp"
#include "Visitor/IDictionaryVisitor.hpp"
#include "Reports/ReportData.hpp"

template <typename Key, typename Value>
class ReportDataCollectorVisitor : public IDictionaryVisitor<Key, Value> {
    ReportData& report;

    void addComparisonsCount(const IDictionary& dict);

    void setDictionaryType(const std::string& dictType);
public:
    ReportDataCollectorVisitor(ReportData& data);

    void collectMetrics(const AVLTree<Key, Value>& avlTree);
    void collectMetrics(const RedBlackTree<Key, Value>& redBlackTree);
    void collectMetrics(const ChainedHashTable<Key, Value>& chainedHashTable);
    void collectMetrics(const OpenAddressingHashTable<Key, Value>& openAddressingHashTable);
};

#include "Visitor/ReportDataCollectorVisitor.impl.hpp"

#endif
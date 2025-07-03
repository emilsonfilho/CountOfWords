#ifndef REPORT_DATA_VISITOR_HPP
#define REPORT_DATA_VISITOR_HPP

#include <functional>

#include "Visitor/IDictionaryVisitor.hpp"
#include "Reports/ReportData.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ReportDataCollectorVisitor : public IDictionaryVisitor<Key, Value> {
    ReportData& report;

    template <typename Dictionary>
    void addComparisonsCount(const Dictionary& dict);

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
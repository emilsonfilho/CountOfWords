#include "Visitor/ReportDataCollectorVisitor.hpp"

template <typename Key, typename Value, typename Hash>
template <typename Dictionary>
void ReportDataCollectorVisitor<Key, Value, Hash>::addComparisonsCount(const Dictionary& dict) {
    report.comparisons = dict.getComparisonsCount();
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::setDictionaryType(const std::string& dictType) {
    report.dictionaryType = dictType;
}

template <typename Key, typename Value, typename Hash>
ReportDataCollectorVisitor<Key, Value, Hash>::ReportDataCollectorVisitor(ReportData& data)
    : report(data) {}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const AVLTree<Key, Value>& avlTree) {
    setDictionaryType("Árvore AVL");
    addComparisonsCount(avlTree);
    report.specificMetric = {"rotações", avlTree.getRotationsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const RedBlackTree<Key, Value>& redBlackTree) {
    setDictionaryType("Árvore Rubro-Negra");
    addComparisonsCount(redBlackTree);
    report.specificMetric = {"rotações", avlTree.getRotationsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const ChainedHashTable<Key, Value>& chainedHashTable) {
    setDictionaryType("Tabela Hash por Encademaneto Exterior");
    addComparisonsCount(ChainedHashTable);
}
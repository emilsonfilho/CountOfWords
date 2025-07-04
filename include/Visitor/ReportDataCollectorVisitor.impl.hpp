#include "Visitor/ReportDataCollectorVisitor.hpp"

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::addComparisonsCount(const IDictionary<Key, Value>& dict) {
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
    report.specificMetric = {"rotações", redBlackTree.getRotationsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const ChainedHashTable<Key, Value, Hash>& chainedHashTable) {
    setDictionaryType("Tabela Hash por Encadeamento Exterior");
    addComparisonsCount(chainedHashTable);
    report.specificMetric = {"colisões", chainedHashTable.getCollisionsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const OpenAddressingHashTable<Key, Value, Hash>& openAddressingHashTable) {
    setDictionaryType("Tabela Hash por Endereçamento Aberto");
    addComparisonsCount(openAddressingHashTable);
    report.specificMetric = {"colisões", openAddressingHashTable.getCollisionsCount()};
}
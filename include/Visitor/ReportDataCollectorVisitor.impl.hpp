#include "Visitor/ReportDataCollectorVisitor.hpp"

#include "Utils/Casting/Casting.hpp"
#include "Trees/AVL/AVLTree.hpp"
#include "Trees/RedBlack/RedBlackTree.hpp"
#include "HashTables/Chained/ChainedHashTable.hpp"
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

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
    addComparisonsCount(Casting::toIDictionary<Key, Value, AVLTree<Key, Value>>(avlTree));
    report.specificMetric = {"rotações", avlTree.getRotationsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const RedBlackTree<Key, Value>& redBlackTree) {
    setDictionaryType("Árvore Rubro-Negra");
    addComparisonsCount(Casting::toIDictionary<Key, Value, RedBlackTree<Key, Value>>(redBlackTree));
    report.specificMetric = {"rotações", redBlackTree.getRotationsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const ChainedHashTable<Key, Value, Hash>& chainedHashTable) {
    setDictionaryType("Tabela Hash por Encadeamento Exterior");
    addComparisonsCount(Casting::toIDictionary<Key, Value, ChainedHashTable<Key, Value, Hash>>(chainedHashTable));
    report.specificMetric = {"colisões", chainedHashTable.getCollisionsCount()};
}

template <typename Key, typename Value, typename Hash>
void ReportDataCollectorVisitor<Key, Value, Hash>::collectMetrics(const OpenAddressingHashTable<Key, Value, Hash>& openAddressingHashTable) {
    setDictionaryType("Tabela Hash por Endereçamento Aberto");
    addComparisonsCount(Casting::toIDictionary<Key, Value, OpenAddressingHashTable<Key, Value, Hash>>(openAddressingHashTable));
    report.specificMetric = {"colisões", openAddressingHashTable.getCollisionsCount()};
}
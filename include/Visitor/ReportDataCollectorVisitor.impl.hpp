#include "Visitor/ReportDataCollectorVisitor.hpp"

#include "Configs/Locale/CollateCompare/CollateCompare.hpp"
#include "HashTables/Chained/ChainedHashTable.hpp"
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"
#include "Trees/AVL/AVLTree.hpp"
#include "Trees/RedBlack/RedBlackTree.hpp"
#include "Utils/Casting/Casting.hpp"

template <typename Key, typename Value>
void ReportDataCollectorVisitor<Key, Value>::addComparisonsCount(
    const IDictionary<Key, Value> &dict) {
  report.comparisons = dict.getComparisonsCount();
}

template <typename Key, typename Value>
void ReportDataCollectorVisitor<Key, Value>::setDictionaryType(
    const std::string &dictType) {
  report.dictionaryType = dictType;
}

template <typename Key, typename Value>
ReportDataCollectorVisitor<Key, Value>::ReportDataCollectorVisitor(
    ReportData &data)
    : report(data) {}

template <typename Key, typename Value>
void ReportDataCollectorVisitor<Key, Value>::collectMetrics(
    const AVLTree<Key, Value, CollateCompare> &avlTree) {
  setDictionaryType("Árvore AVL");
  addComparisonsCount(
      Casting::toIDictionary<Key, Value, AVLTree<Key, Value, CollateCompare>>(avlTree));
  report.specificMetric = {"rotações", avlTree.getRotationsCount()};
}

template <typename Key, typename Value>
void ReportDataCollectorVisitor<Key, Value>::collectMetrics(
    const RedBlackTree<Key, Value, CollateCompare> &redBlackTree) {
  setDictionaryType("Árvore Rubro-Negra");
  addComparisonsCount(
      Casting::toIDictionary<Key, Value, RedBlackTree<Key, Value, CollateCompare>>(
          redBlackTree));
  report.specificMetric = {"rotações", redBlackTree.getRotationsCount()};
}

template <typename Key, typename Value>
void ReportDataCollectorVisitor<Key, Value>::collectMetrics(
    const ChainedHashTable<Key, Value> &chainedHashTable) {
  setDictionaryType("Tabela Hash por Encadeamento Exterior");
  addComparisonsCount(
      Casting::toIDictionary<Key, Value, ChainedHashTable<Key, Value>>(
          chainedHashTable));
  report.specificMetric = {"colisões", chainedHashTable.getCollisionsCount()};
}

template <typename Key, typename Value>
void ReportDataCollectorVisitor<Key, Value>::collectMetrics(
    const OpenAddressingHashTable<Key, Value> &openAddressingHashTable) {
  setDictionaryType("Tabela Hash por Endereçamento Aberto");
  addComparisonsCount(
      Casting::toIDictionary<Key, Value,
                             OpenAddressingHashTable<Key, Value>>(
          openAddressingHashTable));
  report.specificMetric = {"colisões",
                           openAddressingHashTable.getCollisionsCount()};
}
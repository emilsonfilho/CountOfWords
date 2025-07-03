#ifndef IDICTIONARY_VISITOR_HPP
#define IDICTIONARY_VISITOR_HPP

#include "Trees/AVL/AVLTree.hpp"
#include "Trees/RedBlack/RedBlackTree.hpp"
#include "HashTables/Chained/ChainedHashTable.hpp"
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <utility>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class IDictionaryVisitor {
public:
    void collectMetrics(const AVLTree<Key, Value>& avlTree) = 0;
    void collectMetrics(const RedBlackTree<Key, Value>& redBlackTree) = 0;
    void collectMetrics(const ChainedHashTable<Key, Value>& chainedHashTable) = 0;
    void collectMetrics(const OpenAddressingHashTable<Key, Value>& openAddressingHashTable) = 0;
};

#endif
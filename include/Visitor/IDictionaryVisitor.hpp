#ifndef IDICTIONARY_VISITOR_HPP
#define IDICTIONARY_VISITOR_HPP

#include "Trees/AVL/AVLTree.hpp"
#include "Trees/RedBlack/RedBlackTree.hpp"
#include "HashTables/Chained/ChainedHashTable.hpp"
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <utility>


/**
 * @class IDictionaryVisitor
 * @brief An interface (abstract class) for a visitor that collects metrics from dictionary data structures.
 *
 * This class defines the contract for implementing the Visitor design pattern. Concrete
 * implementations of this interface can perform operations, such as collecting performance
 * metrics, on various dictionary-like data structures without modifying their source code.
 *
 * @tparam Key The type of the keys stored in the dictionary.
 * @tparam Value The type of the values stored in the dictionary.
 * @tparam Hash The hash function object type, used for hash-based structures.
 * Defaults to std::hash<Key>.
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class IDictionaryVisitor {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~IDictionaryVisitor() = default;

    /**
     * @brief Pure virtual function to visit an AVLTree.
     *
     * A concrete visitor must implement this method to handle metric collection
     * for an AVLTree.
     *
     * @param avlTree A constant reference to the AVLTree to be visited.
     */
    virtual void collectMetrics(const AVLTree<Key, Value>& avlTree) = 0;

    /**
     * @brief Pure virtual function to visit a RedBlackTree.
     *
     * A concrete visitor must implement this method to handle metric collection
     * for a RedBlackTree.
     *
     * @param redBlackTree A constant reference to the RedBlackTree to be visited.
     */
    virtual void collectMetrics(const RedBlackTree<Key, Value>& redBlackTree) = 0;

    /**
     * @brief Pure virtual function to visit a ChainedHashTable.
     *
     * A concrete visitor must implement this method to handle metric collection
     * for a ChainedHashTable.
     *
     * @param chainedHashTable A constant reference to the ChainedHashTable to be visited.
     */
    virtual void collectMetrics(const ChainedHashTable<Key, Value, Hash>& chainedHashTable) = 0;

    /**
     * @brief Pure virtual function to visit an OpenAddressingHashTable.
     *
     * A concrete visitor must implement this method to handle metric collection
     * for an OpenAddressingHashTable.
     *
     * @param openAddressingHashTable A constant reference to the OpenAddressingHashTable to be visited.
     */
    virtual void collectMetrics(const OpenAddressingHashTable<Key, Value, Hash>& openAddressingHashTable) = 0;
};

#endif
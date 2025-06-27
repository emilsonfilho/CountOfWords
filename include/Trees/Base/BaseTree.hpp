#ifndef BASE_TREE_HPP
#define BASE_TREE_HPP

#include <iostream>

#include "Exceptions/KeyExceptions.hpp"

/**
 * @brief A base template class for tree structures.
 *
 * This class provides common functionality for various tree implementations,
 * such as searching for nodes, finding minimum elements, clearing nodes,
 * in-order traversal, and accessing values by key. It uses the curiously
 * recurring template pattern (CRTP) to interact with derived tree classes.
 *
 * @tparam Tree The derived tree class (CRTP).
 * @tparam Node The node type used in the tree.
 * @tparam Key The type of the keys stored in the tree.
 * @tparam Value The type of the values stored in the tree.
 */
template <typename Tree, typename Node, typename Key, typename Value>
class BaseTree {
    /**
     * @brief Increments a counter in the derived tree class.
     * @details This method uses CRTP to call `incrementCounter()` on the derived `Tree` object.
     */
    void count(size_t n) const;

    void clearCounter();
protected:
    Node* root;
    size_t maxKeyLen;
    size_t maxValLen;

    BaseTree(Node* r);

    /**
     * @brief Finds a node with the specified key in the tree.
     * @param key The key to search for.
     * @return A const pointer to the node if found, nullptr otherwise.
     */
    const Node* findNode(const Key& key, Node* comp = nullptr) const;

    /**
     * @brief Finds the node with the minimum key in the subtree rooted at the given node.
     * @param node The root of the subtree to search within.
     * @return A pointer to the node with the minimum key.
     */
    Node* minimum(Node* node) const;

    /**
     * @brief Recursively clears (deletes) nodes in a subtree, avoiding a comparison node.
     * @details This method is typically used in destructors to deallocate tree nodes.
     * @param node The current node to clear.
     * @param comp A comparison node (e.g., a sentinel or a node not to be deleted).
     */
    void clearNode(Node* node, Node* comp);

    void reset(Node* node, Node* comp = nullptr, Node* defaultRoot = nullptr);

    /**
     * @brief Performs an in-order traversal of the subtree and prints node information to an output stream.
     * @param out The output stream to print to.
     * @param node The current node in the traversal.
     * @param comp A comparison node (e.g., a sentinel node to stop traversal).
     */
    void inOrderTransversal(std::ostream& out, Node* node, Node* comp) const;

    /**
     * @brief Accesses the value associated with a given key.
     * @param key The key whose associated value is to be returned.
     * @return A const reference to the value associated with the key.
     * @throws KeyNotFoundException If the key is not found in the tree.
     */
    const Value& at(const Key& key, Node* comp = nullptr) const;

    void setMaxKeyLen(const Key& key);
    void setMaxValLen(const Value& value);
};

// Include the implementation file to provide the definitions for the template methods.
// This must be at the end of the header file.
#include "Trees/Base/BaseTree.impl.hpp"

#endif

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

    /**
     * @brief Resets the internal counter used for tracking operations or metrics in the tree.
     * 
     * This function delegates the reset operation to the derived class by calling its
     * `resetCounter` method. It ensures that the counter is cleared and ready for reuse.
     */
    void clearCounter();
protected:
    /**
     * @brief Pointer to the root node of the tree.
     * 
     * This member variable represents the starting point of the tree structure.
     * It is used to access and manage all nodes within the tree.
     */
    Node* root;

    /**
     * @brief Represents the maximum length of a key that can be stored in the tree.
     */
    size_t maxKeyLen;

    /**
     * @brief Represents the maximum length of a value in the tree.
     * 
     * This variable is used to define the maximum number of characters
     * or bytes that a value can have when stored in the tree structure.
     */
    size_t maxValLen;
    
    /**
     * @brief Tracks the number of rotations performed in the tree.
     * 
     * This variable is used to count the total number of rotations 
     * (e.g., left or right rotations) that have been executed to 
     * maintain the balance of the tree structure.
     */
    size_t rotationsCount;

    /**
     * @brief Constructs a BaseTree with the given root node.
     * 
     * @param r Pointer to the root node of the tree.
     * 
     * This constructor initializes the BaseTree with the provided root node.
     * It also sets the initial values for the maximum key length, maximum value
     * length, and the rotations count to zero. Additionally, it clears the counter
     * used for tracking operations.
     */
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

    /**
     * @brief Resets the tree by clearing all nodes starting from the given node, 
     *        except for the comparison node, and sets the root to the default root.
     * 
     * @param node The starting node to clear.
     * @param comp The comparison node that will not be cleared. Defaults to nullptr.
     * @param defaultRoot The new root node to set after clearing. Defaults to nullptr.
     */
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

    /**
     * @brief Updates the maximum key length stored in the tree.
     * 
     * This function calculates the length of the given key and updates
     * the `maxKeyLen` member variable if the length of the provided key
     * is greater than the current value of `maxKeyLen`.
     * 
     * @param key The key whose length is to be compared and potentially
     *            used to update the maximum key length.
     */
    void setMaxKeyLen(const Key& key);

    /**
     * @brief Updates the maximum length of the value in the tree.
     * 
     * This function calculates the size of the given value and updates
     * the `maxValLen` member variable if the size of the provided value
     * is greater than the current `maxValLen`.
     * 
     * @param value The value whose size is to be compared and potentially
     *              used to update the maximum value length.
     */
    void setMaxValLen(const Value& value);

    /**
     * @brief Increments the count of rotations performed on the tree.
     * 
     * This function increases the internal counter that tracks the number of 
     * rotations performed during tree operations, such as balancing. By default, 
     * the counter is incremented by 1, but a custom amount can be specified.
     * 
     * @param amount The number by which to increment the rotations count. 
     *               Defaults to 1 if not specified.
     */
    void incrementRotationsCount(size_t amount = 1);
};

// Include the implementation file to provide the definitions for the template methods.
// This must be at the end of the header file.
#include "Trees/Base/BaseTree.impl.hpp"

#endif

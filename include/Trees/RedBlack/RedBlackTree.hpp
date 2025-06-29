#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <iostream>

#include "Dictionary/IDictionary.hpp"
#include "Trees/RedBlack/RedBlackNode.hpp"
#include "Trees/Base/BaseTree.hpp"

/**
 * @brief A class representing a Red-Black Tree.
 * 
 * The RedBlackTree class implements a self-balancing binary search tree that maintains
 * the Red-Black Tree properties. It supports operations such as insertion, deletion,
 * and search while ensuring logarithmic time complexity.
 * 
 * @tparam Key The type of the keys stored in the tree.
 * @tparam Value The type of the values associated with the keys.
 */
template <typename Key, typename Value>
class RedBlackTree : public IDictionary<Key, Value>, public BaseTree<RedBlackTree<Key, Value>, RedBlackNode<Key, Value>, Key, Value> {
private:
    static RedBlackNode<Key, Value> NIL_NODE; ///< Sentinel node representing null leaves.
    static constexpr RedBlackNode<Key, Value>* const NIL = &NIL_NODE; ///< Sentinel node representing null leaves.

    /**
     * @brief Performs a left rotation on a given node.
     * 
     * @param y A pointer to the node to be rotated.
     * @return A pointer to the new root of the subtree after the rotation.
     */
    RedBlackNode<Key, Value>* rotateLeft(RedBlackNode<Key, Value>* y);

    /**
     * @brief Performs a right rotation on a given node.
     * 
     * @param y A pointer to the node to be rotated.
     * @return A pointer to the new root of the subtree after the rotation.
     */
    RedBlackNode<Key, Value>* rotateRight(RedBlackNode<Key, Value>* y);

    /**
     * @brief Fixes the Red-Black Tree properties after an insertion.
     * 
     * This function restores the Red-Black Tree properties by performing rotations
     * and recoloring nodes as necessary.
     * 
     * @param z A pointer to the newly inserted node.
     */
    void insertFixup(RedBlackNode<Key, Value>* z);

    /**
     * @brief Restores the Red-Black Tree properties after a node deletion.
     *
     * This function ensures that the Red-Black Tree remains balanced and maintains
     * its properties (e.g., no two consecutive red nodes, equal black height for all paths)
     * after a node has been deleted. It performs rotations and recoloring as necessary.
     *
     * @param x A pointer to the node that replaces the deleted node, or NIL if no replacement exists.
     *
     * @note This function assumes that the tree is a valid Red-Black Tree before the deletion
     * and that the node being fixed up is initially black.
     */
    void deleteFixup(RedBlackNode<Key, Value>* x);


    /**
     * @brief Deletes a node from the Red-Black Tree.
     * 
     * This function removes the specified node from the tree while maintaining
     * the Red-Black Tree properties. If the node to be deleted has two children,
     * it is replaced with its in-order successor. The function also ensures that
     * the tree remains balanced and adheres to the Red-Black Tree rules by calling
     * the deleteFixup function when necessary.
     * 
     * @param z A pointer to the node to be deleted.
     */
    void deleteNode(RedBlackNode<Key, Value>* z);

    /**
     * @brief Prints the structure of the Red-Black Tree starting from a given node.
     * 
     * @param node A pointer to the current node being printed.
     * @param indent The indentation level for the current node.
     */
    void printTree(RedBlackNode<Key, Value>* node, int indent = 0) const;

public:
    /**
     * @brief Constructs an empty Red-Black Tree.
     */
    RedBlackTree();

    /**
     * @brief Inserts a key-value pair into the Red-Black Tree.
     * 
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const Key& key, const Value& value);

    /**
     * @brief Searches for a key in the Red-Black Tree and retrieves its associated value.
     * 
     * @param key The key to search for.
     * @param outValue A reference to store the associated value if the key is found.
     * @return true If the key is found.
     * @return false If the key is not found.
     */
    bool find(const Key& key, Value& outValue);

    /**
     * @brief Updates the value associated with a given key in the Red-Black Tree.
     * 
     * @param key The key to update.
     * @param value The new value to associate with the key.
     * @throws KeyNotFoundException If the key is not found in the tree.
     */
    void update(const Key& key, const Value& value);

    /**
     * @brief Removes a node with the specified key from the Red-Black Tree.
     * 
     * @param key The key of the node to be removed.
     */
    void remove(const Key& key);

    /**
     * @brief Clears the Red-Black Tree by deallocating all nodes.
     */
    void clear();

    /**
     * @brief Prints the elements of the Red-Black Tree in in-order traversal.
     * 
     * @param out The output stream where the traversal result will be written.
     */
    void printInOrder(std::ostream& out) const;

    /**
     * @brief Retrieves the count of comparisons made during operations on the Red-Black Tree.
     * 
     * @return The total number of comparisons made.
     */
    size_t getComparisonsCount() const;

    /**
     * @brief Accesses the value associated with a given key.
     * 
     * @param key The key to access.
     * @return A reference to the associated value.
     */
    virtual Value& operator[](const Key& key);

    /**
     * @brief Accesses the value associated with a given key (const version).
     * 
     * @param key The key to access.
     * @return A const reference to the associated value.
     */
    virtual const Value& operator[](const Key& key) const;

    /**
     * @brief Prints the structure of the Red-Black Tree.
     */
    void print() const;

    /**
     * @brief Retrieves the total number of rotations performed by the Red-Black Tree.
     * 
     * This method returns the count of rotations (both left and right) that have been
     * executed during insertions or deletions to maintain the Red-Black Tree properties.
     * 
     * @return size_t The total number of rotations performed.
     */
    size_t getRotationsCount() const;
};

#include "Trees/RedBlack/RedBlackTree.impl.hpp"

#endif
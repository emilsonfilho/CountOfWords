#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <iostream>

#include "Dictionary/IDictionary.hpp"
#include "Trees/Base/Node.hpp"
#include "Trees/Base/BaseTree.hpp"
#include "Trees/AVL/AVLNode.hpp"

/**
 * @brief A class representing an AVL Tree.
 * 
 * The AVLTree class implements a self-balancing binary search tree that maintains
 * the AVL property. It supports operations such as insertion, deletion, and search
 * while ensuring logarithmic time complexity.
 * 
 * @tparam Key The type of the keys stored in the tree.
 * @tparam Value The type of the values associated with the keys.
 */
template <typename Key, typename Value>
class AVLTree : public IDictionary<Key, Value>, public BaseTree<AVLTree<Key, Value>, AVLNode<Key, Value>, Key, Value> {
private:
    /**
     * @brief Computes the height of a given node in the AVL tree.
     * 
     * @param node A pointer to the node whose height is to be computed.
     * @return The height of the node. Returns 0 if the node is null.
     */
    size_t height(AVLNode<Key, Value>* node) const;

    /**
     * @brief Calculates the height of the subtree rooted at a given node.
     * 
     * @param node A pointer to the node whose subtree height is to be calculated.
     * @return The height of the subtree rooted at the given node.
     */
    size_t calcHeight(AVLNode<Key, Value>* node) const;

    /**
     * @brief Calculates the balance factor of a given node.
     * 
     * The balance factor is the difference between the height of the right subtree
     * and the height of the left subtree.
     * 
     * @param node A pointer to the node for which the balance factor is calculated.
     * @return The balance factor of the node.
     */
    int getBalanceFactor(AVLNode<Key, Value>* node) const;

    /**
     * @brief Prints the AVL tree structure starting from a given node.
     * 
     * @param node A pointer to the current node being printed.
     * @param depth The depth of the current node in the tree.
     */
    void printTree(AVLNode<Key, Value>* node, size_t depth = 0) const;

    /**
     * @brief Performs a left rotation on a given node.
     * 
     * @param y A reference to the pointer of the node to be rotated.
     * @return A pointer to the new root of the subtree after the rotation.
     */
    AVLNode<Key, Value>* rotateLeft(AVLNode<Key, Value>*& y);

    /**
     * @brief Performs a right rotation on a given node.
     * 
     * @param y A reference to the pointer of the node to be rotated.
     * @return A pointer to the new root of the subtree after the rotation.
     */
    AVLNode<Key, Value>* rotateRight(AVLNode<Key, Value>*& y);

    /**
     * @brief Fixes the balance of a given node in the AVL tree.
     * 
     * This function performs rotations to restore the AVL tree's balance if necessary.
     * 
     * @param node A pointer to the node to be balanced.
     * @return A pointer to the balanced node.
     */
    AVLNode<Key, Value>* fixupNode(AVLNode<Key, Value>* node);

    /**
     * @brief Removes the successor node from the AVL tree.
     * 
     * This function removes the smallest node in the right subtree during deletion.
     * 
     * @param root The root of the subtree where the successor is being removed.
     * @param node The current node being traversed to find the successor.
     * @return A pointer to the updated subtree after removing the successor node.
     */
    AVLNode<Key, Value>* removeSuccessor(AVLNode<Key, Value>* root, AVLNode<Key, Value>* node);

    /**
     * @brief Inserts a key-value pair into the AVL tree.
     * 
     * @param key The key to insert.
     * @param value The value associated with the key.
     * @param node The current node in the recursive insertion process.
     * @return A pointer to the updated node after insertion and balancing.
     * @throws KeyAlreadyExistsException If the key already exists in the tree.
     */
    AVLNode<Key, Value>* insert(const Key& key, const Value& value, AVLNode<Key, Value>* node);

    /**
     * @brief Updates the value associated with a given key in the AVL tree.
     * 
     * @param key The key to update.
     * @param value The new value to associate with the key.
     * @param node The current node being traversed.
     * @return A pointer to the updated node after fixing up the tree structure.
     * @throws KeyNotFoundException If the key is not found in the tree.
     */
    AVLNode<Key, Value>* update(const Key& key, const Value& value, AVLNode<Key, Value>* node);

    /**
     * @brief Removes a node with the specified key from the AVL tree.
     * 
     * @param key The key of the node to be removed.
     * @param node The current node being examined during traversal.
     * @return A pointer to the updated subtree after the removal operation.
     */
    AVLNode<Key, Value>* remove(const Key& key, AVLNode<Key, Value>* node);

    /**
     * @brief Inserts or updates a key-value pair in the AVL tree.
     * @param key The key to be inserted or updated.
     * @param node The current node being processed in the recursive call.
     * @param outValue A reference to a pointer that will store the address of the value associated with the key.
     * @return A pointer to the balanced node after insertion or update.
     * @details This method handles both insertion of new nodes and updating existing
     * node values. It recursively traverses the tree to find the correct position
     * for the key. If the key is found, `outValue` is set to point to the existing
     * value. If a new node is created, `outValue` points to its new value.
     * It also updates `maxKeyLen` and `maxValLen` based on the display size
     * of the key and value, and performs AVL tree rotations via `fixupNode`
     * to maintain balance.
     */
    AVLNode<Key, Value>* upsert(const Key& key, AVLNode<Key, Value>* node, Value*& outValue);

    public:
    static const int IMBALANCE = 2; ///< The imbalance threshold for the AVL tree.
    
    /**
     * @brief Constructs an empty AVL tree.
     */
    AVLTree();
    
    /**
     * @brief Destroys the AVL tree and deallocates all resources.
     */
    ~AVLTree();
    
    /**
     * @brief Inserts a new key-value pair into the AVL tree.
     * @param key The key to be inserted.
     * @param value The value associated with the key.
     * @details This method updates the `root` of the AVL tree after insertion
     * and also updates `maxKeyLen` and `maxValLen` based on the
     * display size of the inserted key and value, respectively.
     */
    void insert(const Key& key, const Value& value) override;
    
    /**
     * @brief Searches for a key in the AVL tree and retrieves its associated value.
     * 
     * @param key The key to search for.
     * @param outValue A reference to store the associated value if the key is found.
     * @return true If the key is found.
     * @return false If the key is not found.
     */
    bool find(const Key& key, Value& outValue) override;
    
    /**
     * @brief Updates the value associated with a given key in the AVL tree.
     * 
     * @param key The key to update.
     * @param value The new value to associate with the key.
     * @throws KeyNotFoundException If the key is not found in the tree.
     */
    void update(const Key& key, const Value& value) override;
    
    /**
     * @brief Removes a node with the specified key from the AVL tree.
     * 
     * @param key The key of the node to be removed.
     */
    void remove(const Key& key) override;
    
    /**
     * @brief Clears the AVL tree by deallocating all nodes.
     */
    void clear() override;
    
    /**
     * @brief Prints the elements of the AVL tree in in-order traversal.
     * 
     * @param out The output stream where the traversal result will be written.
     */
    void printInOrder(std::ostream& out) const override;
    
    /**
     * @brief Retrieves the count of comparisons made during operations on the AVL tree.
     * 
     * @return The total number of comparisons made.
     */
    size_t getComparisonsCount() const override;
    
    /**
     * @brief Accesses the value associated with a given key.
     * 
     * @param key The key to access.
     * @return A reference to the associated value.
     */
    Value& operator[](const Key& key) override;
    
    /**
     * @brief Accesses the value associated with a given key (const version).
     * 
     * @param key The key to access.
     * @return A const reference to the associated value.
     */
    const Value& operator[](const Key& key) const override;
    
    /**
     * @brief Prints the AVL tree structure.
     */
    void print() const;

    size_t getRotationsCount() const;
};

#include "Trees/AVL/AVLTree.impl.hpp"

#endif

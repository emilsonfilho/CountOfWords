#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <iostream>

#include "IDictionary.hpp"
#include "INode.hpp"

template <typename Key, typename Value>
class AVLTree : public IDictionary<Key, Value> {
public:
    struct Node : public INode<Key, Value> {
        std::pair<Key, Value> data;
        Node *left, *right;
        size_t height;

        /**
         * @brief Constructs a Node object with the given key and value.
         * 
         * @param k The key associated with the node.
         * @param v The value associated with the node.
         */
        Node(const Key& k, const Value& v);

        /**
         * @brief Retrieves the key associated with the current node in the AVL tree.
         * 
         * @return A constant reference to the key of the node.
         */
        const Key& getKey() const override;

        /**
         * @brief Sets the key for the current node in the AVL tree.
         * 
         * @param key The key value to be assigned to the node.
         */
        void setKey(const Key& key) override;
    };
private:
    Node* root;
    size_t comparisonsCount;

    /**
    * @brief Computes the height of a given node in the AVL tree.
    * 
    * This function returns the height of the specified node. If the node is
    * null, it returns 0, indicating that the height of an empty subtree is zero.
    * 
    * @param node A pointer to the node whose height is to be computed.
    * @return size_t The height of the node. Returns 0 if the node is null.
    */
    size_t height(Node* node) const;

    /**
    * @brief Calculates the height of a given node in the AVL tree.
    * 
    * This function computes the height of the subtree rooted at the specified node.
    * The height is defined as the number of edges on the longest path from the node
    * to a leaf. If the node is null, the height is considered to be 0.
    * 
    * @param node A pointer to the node whose height is to be calculated.
    * @return size_t The height of the subtree rooted at the given node.
    */
    size_t calcHeight(Node* node) const;

    /**
    * @brief Calculates the balance factor of a given node in the AVL tree.
    * 
    * The balance factor is defined as the difference between the height of the 
    * right subtree and the height of the left subtree of the node. It is used 
    * to determine whether the tree is balanced at the given node.
    * 
    * @param node A pointer to the node for which the balance factor is calculated.
    *             If the node is null, the balance factor is considered to be 0.
    * @return An integer representing the balance factor of the node. A positive 
    *         value indicates the right subtree is taller, a negative value 
    *         indicates the left subtree is taller, and 0 indicates both subtrees 
    *         have the same height.
    */
    int getBalanceFactor(Node* node) const;

    /**
    * @brief Finds the node with the minimum key in the subtree rooted at the given node.
    * 
    * This function recursively traverses the left child of the given node until it
    * reaches the leftmost node, which contains the smallest key in the subtree.
    * 
    * @param node Pointer to the root of the subtree where the minimum key is to be found.
    * @return Pointer to the node containing the minimum key in the subtree.
    *         If the given node is nullptr, behavior is undefined.
    */
    Node* minimum(Node* node) const;

    void printTree(Node* node, size_t depth = 0) const;

    /**
    * @brief Performs a left rotation on the given node in the AVL tree.
    * 
    * This function adjusts the structure of the AVL tree to maintain its balance
    * by rotating the subtree rooted at the given node to the left. It updates the
    * heights of the affected nodes after the rotation.
    * 
    * @param y A reference to the pointer of the node to be rotated.
    * @return A pointer to the new root of the subtree after the left rotation.
    */
    Node* rotateLeft(Node*& y);

    /**
    * Performs a right rotation on the given node in the AVL tree.
    *
    * A right rotation is used to balance the AVL tree when the left subtree
    * of a node becomes taller than the right subtree. This operation adjusts
    * the structure of the tree while maintaining the binary search tree property.
    *
    * @param y A reference to the node where the rotation is performed.
    * @return A pointer to the new root of the subtree after the rotation.
    */
    Node* rotateRight(Node*& y);

    /**
    * @brief Fixes the balance of a given node in the AVL tree.
    *
    * This function checks the balance factor of the provided node and performs
    * rotations to restore the AVL tree's balance if necessary. It handles both
    * left and right imbalances by applying the appropriate single or double
    * rotations. After balancing, it updates the height of the node.
    *
    * @param y Pointer to the node to be fixed up.
    * @return Pointer to the balanced node after rotations and height update.
    */
    Node* fixupNode(Node* node);

    /**
    * @brief Removes the successor node from the AVL tree and updates the tree structure.
    * 
    * This function is used to remove the successor node (the smallest node in the right subtree)
    * during deletion operations in an AVL tree. It recursively traverses the left subtree until
    * it finds the successor node, updates the key of the root node, and adjusts the tree structure
    * to maintain the AVL tree properties.
    * 
    * @param root The root node of the subtree where the successor is being removed.
    * @param node The current node being traversed to find the successor.
    * @return Node* The updated subtree after removing the successor node.
    */
    Node* removeSuccessor(Node* root, Node* node);

    /**
    * Inserts a key-value pair into the AVL tree, maintaining the AVL property.
    * 
    * @param key The key to insert into the tree.
    * @param value The value associated with the key.
    * @param node The current node being processed during the insertion.
    *             This is typically the root of the subtree where the insertion is happening.
    * 
    * @return A pointer to the updated node after insertion and rebalancing.
    *         If the key already exists, the value is updated and the node is returned.
    * 
    * @note This function assumes that it will never be called with a nullptr root node.
    *       If the key is less than the current node's key, the insertion proceeds to the left subtree.
    *       If the key is greater, the insertion proceeds to the right subtree.
    *       If the key matches the current node's key, the value is updated.
    * 
    * @warning The caller is responsible for managing the memory of the newly created nodes.
    */
    Node* insert(const Key& key, const Value& value, Node* node);

    /**
    * @brief Searches for a key in the AVL tree and retrieves its associated value.
    * 
    * This function performs a recursive search starting from the given node to find
    * the specified key. If the key is found, the associated value is stored in the
    * provided output parameter `outValue`. The function also increments the 
    * `comparisonsCount` variable to track the number of comparisons made during the search.
    * 
    * @param key The key to search for in the AVL tree.
    * @param outValue Reference to a variable where the associated value will be stored if the key is found.
    * @param node Pointer to the current node in the AVL tree during the recursive search.
    * @return true If the key is found in the AVL tree.
    * @return false If the key is not found in the AVL tree.
    */
    bool find(const Key& key, Value& outValue, Node* node);

    /**
    * @brief Updates the value associated with a given key in the AVL tree. If the key does not exist, 
    *        a new node is created and inserted into the tree.
    * 
    * @param key The key to be updated or inserted into the tree.
    * @param value The value to be associated with the given key.
    * @param node The current node being processed in the recursive update operation.
    * 
    * @return A pointer to the updated node after the operation, ensuring the AVL tree remains balanced.
    * 
    * @details This function performs the following operations:
    *          - If the node is null, a new node is created with the given key and value.
    *          - If the key is less than the current node's key, the function recursively updates the left subtree.
    *          - If the key is greater than the current node's key, the function recursively updates the right subtree.
    *          - If the key matches the current node's key, the value is updated.
    *          - After any modification, the node is rebalanced to maintain AVL tree properties.
    */
    Node* update(const Key& key, const Value& value, Node* node);

    /**
    * @brief Removes a node with the specified key from the AVL tree.
    * 
    * This function recursively traverses the tree to locate the node with the given key.
    * If the node is found, it is removed while maintaining the AVL tree properties.
    * The function also handles cases where the node has no children, one child, or two children.
    * After removal, the tree is rebalanced to ensure AVL properties are preserved.
    * 
    * @param key The key of the node to be removed.
    * @param node The current node being examined during the recursive traversal.
    * @return A pointer to the updated subtree after the removal operation.
    */
    Node* remove(const Key& key, Node* node);

    /**
    * @brief Recursively clears all nodes in the AVL tree starting from the given node.
    * 
    * This function traverses the tree in a post-order manner, deleting all nodes
    * to free memory. It ensures that both left and right child nodes are cleared
    * before deleting the current node.
    * 
    * @param node Pointer to the current node to be cleared. If the node is nullptr,
    *             the function does nothing.
    */
    void clear(Node* node);

    /**
    * @brief Prints the elements of the AVL tree in in-order traversal.
    * 
    * This function recursively traverses the tree in in-order (left subtree, 
    * current node, right subtree) and outputs the key-value pairs stored in 
    * the nodes to the provided output stream.
    * 
    * @param out The output stream where the key-value pairs will be printed.
    * @param node The current node being processed in the traversal.
    *             If the node is nullptr, the function does nothing.
    */
    void printInOrder(std::ostream& out, Node* node) const;
public:
    static const int IMBALANCE = 2;

    /**
    * @brief Constructor for the AVLTree class.
    * 
    * Initializes an empty AVL tree with the root set to nullptr and the 
    * comparisons count initialized to 0.
    */
    AVLTree();
    
    /**
    * @brief Destructor for the AVLTree class.
    *
    * This destructor ensures that all dynamically allocated resources
    * associated with the AVLTree instance are properly released by
    * calling the `clear()` method to deallocate and clean up the tree.
    */
    ~AVLTree();

    /**
    * @brief Inserts a key-value pair into the AVL tree.
    * 
    * This function inserts a new key-value pair into the AVL tree, maintaining
    * the AVL tree's balance properties. If the key already exists in the tree,
    * the corresponding value will be updated.
    * 
    * @param key The key to be inserted into the tree.
    * @param value The value associated with the key.
    */
    void insert(const Key& key, const Value& value) override;

    /**
    * @brief Searches for a key in the AVL tree and retrieves its associated value.
    * 
    * This function attempts to find the specified key in the AVL tree. If the key
    * is found, the associated value is stored in the provided output parameter.
    * 
    * @param key The key to search for in the AVL tree.
    * @param outValue A reference to a variable where the associated value will be stored if the key is found.
    * @return true If the key is found in the AVL tree.
    * @return false If the key is not found in the AVL tree.
    */
    bool find(const Key& key, Value& outValue) override;

    /**
    * @brief Updates the value associated with a given key in the AVL tree.
    * 
    * This function modifies the tree by updating the value of the specified key.
    * If the key does not exist in the tree, it may insert a new node with the given key and value.
    * The tree's balance is maintained after the update operation.
    * 
    * @param key The key whose associated value is to be updated.
    * @param value The new value to associate with the key.
    */
    void update(const Key& key, const Value& value) override;

    /**
    * @brief Removes a node with the specified key from the AVL tree.
    * 
    * This function removes the node containing the given key from the AVL tree
    * while maintaining the AVL tree properties (balance and binary search tree structure).
    * 
    * @param key The key of the node to be removed.
    */
    void remove(const Key& key) override;

    /**
    * @brief Clears the AVL tree by deallocating all nodes and resetting the root to nullptr.
    * 
    * This function recursively clears all nodes in the tree starting from the root,
    * effectively removing all key-value pairs stored in the tree. After the operation,
    * the tree will be empty.
    */
    void clear() override;

    /**
    * @brief Prints the elements of the AVL tree in in-order traversal to the specified output stream.
    * 
    * This function performs an in-order traversal of the AVL tree, starting from the root node,
    * and writes the key-value pairs to the provided output stream.
    * 
    * @param os The output stream where the in-order traversal result will be written.
    */
    void printInOrder(std::ostream& out) const override;
    
    /**
    * @brief Retrieves the count of comparisons made during operations on the AVL tree.
    * 
    * This method returns the number of comparisons performed, which can be useful
    * for analyzing the efficiency of the tree's operations.
    * 
    * @return size_t The total number of comparisons made.
    */
    size_t getComparisonsCount() const override;

    void print() const;
};

#include "AVLTree/AVLTree.impl.hpp"

#endif

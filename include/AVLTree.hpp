#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <iostream>

#include "IDictionary.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class AVLTree : public IDictionary<Key, Value> {
public:
    struct Node {
        std::pair<Key, Value> data;
        Node *left, *right;
        size_t height;

        Node(const Key& k, const Value& v);
    };
private:
    Node* root;
    int comparisonsCount;

    size_t height(Node* node) const {
        if (!node) return 0;

        return node->height;
    }

    size_t calcHeight(Node* node) const {
        if (!node) return 0;

        size_t leftHeight = height(node->left),
               rightHeight = height(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    int getBalanceFactor(Node* node) const {
        if (!node) return 0;
        return height(node->right) - height(node->left);
    }

    bool isLeaf(Node* node) const {
        return !node->left and !node->right;
    }

    Node* minimum(Node* node) const {
        if (!node->left) return node;
        return minimum(node->left);
    }

    void printTree(Node* node, size_t depth = 0) const;

    Node* rotateLeft(Node*& y);

    Node* rotateRight(Node*& y);

    Node* fixupNode(Node* node);

    Node* removeSuccessor(Node* root, Node* node);

    Node* insert(const Key& key, const Value& value, Node* node);
    bool find(const Key& key, Value& outValue, Node* node);
    Node* update(const Key& key, const Value& value, Node* node);
    Node* remove(const Key& key, Node* node);
public:
    static const int IMBALANCE = 2;

    AVLTree();

    void insert(const Key& key, const Value& value) override;
    bool find(const Key& key, Value& outValue) override;
    void update(const Key& key, const Value& value) override;
    void remove(const Key& key) override;
    void clear() override {};
    void printInOrder(std::ostream& out) override {};
    size_t getComparisonsCount() const override { return 0; };

    void print() const;
};

#include "AVLTree.impl.hpp"

#endif

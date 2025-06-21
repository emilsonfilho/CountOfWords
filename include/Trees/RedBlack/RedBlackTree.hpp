#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <iostream>

#include "Dictionary/IDictionary.hpp"
#include "Trees/RedBlack/RedBlackNode.hpp"
#include "Trees/Base/BaseTree.hpp"

template <typename Key, typename Value>
class RedBlackTree : public IDictionary<Key, Value>, public BaseTree<RedBlackTree<Key, Value>, RedBlackNode<Key, Value>, Key, Value> {
private:
    RedBlackNode<Key, Value>* root;
    static RedBlackNode<Key, Value>* const NIL;

    const RedBlackNode<Key, Value>* getRoot() const;

    RedBlackNode<Key, Value>* rotateLeft(RedBlackNode<Key, Value>* y);
    RedBlackNode<Key, Value>* rotateRight(RedBlackNode<Key, Value>* y);

    void insertFixup(RedBlackNode<Key, Value>* z);

    RedBlackNode<Key, Value>* update(const Key& key, const Value& value, RedBlackNode<Key, Value>* node) {
        if (node == NIL) return node;

        if (key < node->getKey()) {
            
        }

        this->incrementCounter();
    }

    void printTree(RedBlackNode<Key, Value>* node, int indent = 0) const;
public:
    RedBlackTree();

    void insert(const Key& key, const Value& value);
    bool find(const Key& key, Value& outValue);
    void update(const Key& key, const Value& value);
    void remove(const Key& key) {};
    void clear() {};
    void printInOrder(std::ostream& out) const {};
    size_t getComparisonsCount() const { return 0; };
    virtual Value& operator[](const Key& key) { return root->getValue(); }
    virtual const Value& operator[](const Key& key) const { return root->getValue(); };

    void print() const;

    template <typename Tree, typename Node, typename K, typename V>
    friend class BaseTree;
};

#include "Trees/RedBlack/RedBlackTree.impl.hpp"

#endif
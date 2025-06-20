#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <iostream>

#include "IDictionary.hpp"
#include "Node.hpp"

template <typename Key, typename Value>
class RedBlackTree : public IDictionary<Key, Value> {
private:
    enum Color { RED, BLACK };

    struct RedBlackNode : public Node<Key, Value> {
        RedBlackNode* left;
        RedBlackNode* right;
        RedBlackNode* parent;
        Color color;

        RedBlackNode(const Key& k, const Value& v, 
                 RedBlackNode* l, RedBlackNode* r, 
                 RedBlackNode* p, Color c);
    };

    RedBlackNode* root;
    static RedBlackNode* const NIL;

    RedBlackNode* rotateLeft(RedBlackNode* y);
    RedBlackNode* rotateRight(RedBlackNode* y);

    void insertFixup(RedBlackNode* z);

    void printTree(RedBlackNode* node, int indent = 0) const;
public:
    RedBlackTree();

    void insert(const Key& key, const Value& value);
    bool find(const Key& key, Value& outValue) { return false; };
    void update(const Key& key, const Value& value) {};
    void remove(const Key& key) {};
    void clear() {};
    void printInOrder(std::ostream& out) const {};
    size_t getComparisonsCount() const { return 0; };
    virtual Value& operator[](const Key& key) { return root->getValue(); }
    virtual const Value& operator[](const Key& key) const { return root->getValue(); };

    void print() const;
};

#include "RedBlackTree/RedBlackTree.impl.hpp"

#endif
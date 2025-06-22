#ifndef RED_BLACK_NODE_HPP
#define RED_BLACK_NODE_HPP

#include "Trees/Base/Node.hpp"
#include "Trees/RedBlack/Color.hpp"

template <typename Key, typename Value>
struct RedBlackNode : public Node<Key, Value> {
    RedBlackNode* left;
    RedBlackNode* right;
    RedBlackNode* parent;
    Color color;

    RedBlackNode(const Key& k, const Value& v, 
                RedBlackNode* l, RedBlackNode* r, 
                RedBlackNode* p, Color c)
    : Node<Key, Value>(k, v), left(l), right(r), parent(p), color(c) {}
};

#endif
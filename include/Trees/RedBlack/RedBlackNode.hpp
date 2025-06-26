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

    /**
     * @brief Constructs a RedBlackNode.
     *
     * @param k The key for the node.
     * @param v The value for the node.
     * @param l Pointer to the left child node.
     * @param r Pointer to the right child node.
     * @param p Pointer to the parent node.
     * @param c The color of the node (Red or Black).
     */
    RedBlackNode(const Key& k, const Value& v, 
                    RedBlackNode* l, RedBlackNode* r, 
                    RedBlackNode* p, Color c)
        : Node<Key, Value>(k, v), left(l), right(r), parent(p), color(c) {}

    RedBlackNode(Color color = BLACK) : Node<Key, Value>(Key(), Value()) {
        this->left = this;
        this->right = this;
        this->parent = this;
        this->color = color;
    }
};

#endif
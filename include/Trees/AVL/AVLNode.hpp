#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

#include "Trees/Base/Node.hpp"

template <typename Key, typename Value>
struct AVLNode : public Node<Key, Value> {
    AVLNode *left, *right;
    size_t height;

    /**
    * @brief Constructs a Node object with the given key and value.
    * 
    * @param k The key associated with the node.
    * @param v The value associated with the node.
    */
    AVLNode(const Key& k, const Value& v)
        : Node<Key, Value>(k, v), left(nullptr), right(nullptr), height(1) {}
};

#endif

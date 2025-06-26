#ifndef BASE_TREE_IMPL_HPP
#define BASE_TREE_IMPL_HPP

#include "Trees/Base/BaseTree.hpp" 

#include <cmath>

#include "Utils/StringHandler.hpp"

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::count() const {
    static_cast<const Tree*>(this)->incrementCounter();
}

template <typename Tree, typename Node, typename Key, typename Value>
const Node* BaseTree<Tree, Node, Key, Value>::getTreeRoot() const {
    return static_cast<const Tree*>(this)->getRoot();
}

template <typename Tree, typename Node, typename Key, typename Value>
const size_t BaseTree<Tree, Node, Key, Value>::getMaxKeyLen() const {
    return static_cast<const Tree*>(this)->maxKeyLen;
}

template <typename Tree, typename Node, typename Key, typename Value>
const size_t BaseTree<Tree, Node, Key, Value>::getMaxValLen() const {
    return static_cast<const Tree*>(this)->maxValLen;
}

template <typename Tree, typename Node, typename Key, typename Value>
const Node* BaseTree<Tree, Node, Key, Value>::findNode(const Key& key, Node* comp) const {
    const Node* aux = getTreeRoot();
    
    while (aux != comp) {
        count();
        if (key < aux->getKey()) {
            aux = aux->left;
        } else if (key > aux->getKey()) {
            aux = aux->right;
        } else {
            return aux;
        }
    }

    return nullptr;       
}

template <typename Tree, typename Node, typename Key, typename Value>
Node* BaseTree<Tree, Node, Key, Value>::minimum(Node* node) const {
    if (!node->left) return node;
    return minimum(node->left);
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::clearNode(Node* node, Node* comp) {
    if (node != comp) {
        clearNode(node->left, comp);
        clearNode(node->right, comp);
        delete node;
    }
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::inOrderTransversal(std::ostream& out, Node* node, Node* comp) const {
    if (node != comp) {
        inOrderTransversal(out, node->left, comp);

        out << StringHandler::SetWidthAtLeft(node->getKey(), getMaxKeyLen()) << " | " 
            << StringHandler::SetWidthAtLeft(node->getValue(), getMaxValLen()) << '\n';

        inOrderTransversal(out, node->right, comp);
    }
}

template <typename Tree, typename Node, typename Key, typename Value>
const Value& BaseTree<Tree, Node, Key, Value>::at(const Key& key) const {
    const Node* aux = getTreeRoot();

    while (aux) {
        count();

        if (key < aux->getKey()) {
            aux = aux->left;
        } else if (key > aux->getKey()) {
            aux = aux->right;
        } else {
            return aux->getValue();
        }
    }

    throw KeyNotFoundException();
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::setMaxKeyLen(const Key& key) {
    static_cast<Tree*>(this)->maxKeyLen = std::max(getMaxKeyLen(), StringHandler::size(key));
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::setMaxValLen(const Value& value) {
    static_cast<Tree*>(this)->maxValLen = std::max(getMaxValLen(), StringHandler::size(value));
}

#endif 

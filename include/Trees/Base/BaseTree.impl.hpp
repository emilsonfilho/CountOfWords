#ifndef BASE_TREE_IMPL_HPP
#define BASE_TREE_IMPL_HPP

#include "Trees/Base/BaseTree.hpp" 

#include <cmath>

#include "Utils/Strings/StringHandler.hpp"

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::count(size_t n) const {
    static_cast<const Tree*>(this)->incrementCounter(n);
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::clearCounter() {
    static_cast<Tree*>(this)->resetCounter();
}

template <typename Tree, typename Node, typename Key, typename Value>
BaseTree<Tree, Node, Key, Value>::BaseTree(Node* r)
    : root(r), maxKeyLen(0), maxValLen(0), rotationsCount(0) {
        clearCounter();
    }

template <typename Tree, typename Node, typename Key, typename Value>
const Node* BaseTree<Tree, Node, Key, Value>::findNode(const Key& key, Node* comp) const {
    const Node* aux = root;
    
    while (aux != comp) {
        if (key < aux->getKey()) {
            count(1);
            aux = aux->left;
        } else if (key > aux->getKey()) {
            count(2);
            aux = aux->right;
        } else {
            count(2);
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
void BaseTree<Tree, Node, Key, Value>::reset(Node* node, Node* comp, Node* defaultRoot) {
    clearNode(node, comp);
    root = defaultRoot;
    maxKeyLen = 0;
    maxValLen = 0;
    rotationsCount = 0;
    clearCounter();
}


template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::inOrderTransversal(std::ostream& out, Node* node, Node* comp) const {
    if (node != comp) {
        inOrderTransversal(out, node->left, comp);

        out << StringHandler::SetWidthAtLeft(node->getKey(), maxKeyLen) << " | " 
            << StringHandler::SetWidthAtLeft(node->getValue(), maxValLen) << '\n';

        inOrderTransversal(out, node->right, comp);
    }
}

template <typename Tree, typename Node, typename Key, typename Value>
const Value& BaseTree<Tree, Node, Key, Value>::at(const Key& key, Node* comp) const {
    const Node* aux = root;

    while (aux != comp) {
        if (key < aux->getKey()) {
            count(1);
            aux = aux->left;
        } else if (key > aux->getKey()) {
            count(2);
            aux = aux->right;
        } else {
            count(2);
            return aux->getValue();
        }
    }

    throw KeyNotFoundException();
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::setMaxKeyLen(const Key& key) {
    maxKeyLen = std::max(maxKeyLen, StringHandler::size(key));
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::setMaxValLen(const Value& value) {
    maxValLen = std::max(maxValLen, StringHandler::size(value));
}

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::incrementRotationsCount(size_t amount) {
    rotationsCount += amount;
}

#endif 

#ifndef BASE_TREE_IMPL_HPP
#define BASE_TREE_IMPL_HPP

#include "Trees/Base/BaseTree.hpp" 

template <typename Tree, typename Node, typename Key, typename Value>
void BaseTree<Tree, Node, Key, Value>::count() const {
    static_cast<const Tree*>(this)->incrementCounter();
}

template <typename Tree, typename Node, typename Key, typename Value>
const Node* BaseTree<Tree, Node, Key, Value>::getTreeRoot() const {
    return static_cast<const Tree*>(this)->getRoot();
}

template <typename Tree, typename Node, typename Key, typename Value>
const Node* BaseTree<Tree, Node, Key, Value>::findNode(const Key& key) const {
    const Node* aux = getTreeRoot();

    while (aux) {
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

        out << node->show() << '\n';

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

#endif 

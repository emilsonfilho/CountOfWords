#ifndef BASE_TREE_HPP
#define BASE_TREE_HPP

#include <iostream>

template <typename Tree, typename Node, typename Key, typename Value>
class BaseTree {
    void count() const {
        static_cast<const Tree*>(this)->incrementCounter();
    }
protected:
    const Node* findNode(const Key& key) const {
        const Node* aux = static_cast<const Tree*>(this)->getRoot();

        while (aux) {
            if (key < aux->getKey()) {
                count();
                aux = aux->left;
            } else if (key > aux->getKey()) {
                count();
                aux = aux->right;
            } else {
                count();
                return aux;
            }
        }

        return nullptr;        
    }

    Node* minimum(Node* node) const {
        if (!node->left) return node;
        return minimum(node->left);
    }

    void clearNode(Node* node, Node* comp) {
        if (node != comp) {
            clearNode(node->left, comp);
            clearNode(node->right, comp);
            delete node;
        }
    }
};

#endif

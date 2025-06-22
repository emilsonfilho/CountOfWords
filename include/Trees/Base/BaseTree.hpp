#ifndef BASE_TREE_HPP
#define BASE_TREE_HPP

#include <iostream>

#include "Exceptions/KeyExceptions.hpp"

template <typename Tree, typename Node, typename Key, typename Value>
class BaseTree {
    void count() const {
        static_cast<const Tree*>(this)->incrementCounter();
    }

    const Node* getTreeRoot() const {
        return static_cast<const Tree*>(this)->getRoot();
    }
protected:
    const Node* findNode(const Key& key) const {
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

    void inOrderTransversal(std::ostream& out, Node* node, Node* comp) const {
        if (node != comp) {
            inOrderTransversal(out, node->left, comp);

            out << node->show() << '\n';

            inOrderTransversal(out, node->right, comp);
        }
    }

    const Value& at(const Key& key) const {
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
};

#endif

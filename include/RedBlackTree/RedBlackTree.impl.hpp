#include "RedBlackTree/RedBlackTree.hpp"

#include "Exceptions/KeyExceptions.hpp"

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackNode::RedBlackNode(
    const Key& k, const Value& v, RedBlackNode* l, RedBlackNode* r, RedBlackNode* p, Color c
) : Node<Key, Value>(k, v), left(l), right(r), parent(p), color(c) {}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackNode* RedBlackTree<Key, Value>::rotateLeft(RedBlackNode* y) {
	RedBlackNode* x = y->right;

	y->right = x->left;
    if (y->right != NIL) y->right->parent = y;
	x->left = y;

    x->parent = y->parent;
    y->parent = x;
    
    if (x->parent != NIL) {
        if (x->getKey() < x->parent->getKey())
            x->parent->right = x;
        else
            x->parent->left = x;
    } else {
        root = x;
    }

	return x;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackNode* RedBlackTree<Key, Value>::rotateRight(RedBlackNode* y) {
	RedBlackNode* x = y->left;

	y->left = x->right;
    if (y->left != NIL) y->left->parent = y;
	x->right = y;

    x->parent = y->parent;
    y->parent = x;
    
    if (x->parent != NIL) {
        if (x->getKey() < x->parent->getKey())
            x->parent->left = x;
        else
            x->parent->right = x;
    } else {
        root = x;
    }

	return x;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insertFixup(RedBlackNode* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            if (z->parent->parent->right->color == RED) { // Case 1
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z->parent->parent->right->color = BLACK;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { // Case 2
                    z = z->parent;
                    z = rotateLeft(z);
                    z = z->left;
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = rotateRight(z->parent->parent);
            }
        } else { // Symmetrical case
            if (z->parent->parent->left->color == RED) { // Case 1
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z->parent->parent->left->color = BLACK;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { // Case 2
                    z = z->parent;
                    z = rotateRight(z);
                    z = z->right;
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = rotateLeft(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::RedBlackNode* const 
RedBlackTree<Key, Value>::NIL = new RedBlackNode(
    Key(), Value(), NIL, NIL, NIL, BLACK
);

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() { root = NIL; }

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    RedBlackNode *z = new RedBlackNode(key, value, NIL, NIL, NIL, RED);

    RedBlackNode *x = root, *y = NIL;
    
    while (x != NIL) {
        y = x;

        if (z->getKey() < x->getKey()) {
            this->incrementCounter();
            x = x->left;
        } else if (z->getKey() > x->getKey()) {
            this->incrementCounter();
            x = x->right;
        } else {
            throw KeyNotFoundException();
        }
    }

    z->parent = y;
    if (y == NIL) 
        root = z;
    else if (z->getKey() < y->getKey())
        y->left = z;
    else
        y->right = z;

    // should I increment counter here?
    this->incrementCounter();

    insertFixup(z);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::printTree(RedBlackNode* node, int indent) const {
    if (node != NIL) {
        printTree(node->right, indent + 4);

        if (indent > 0) {
            std::cout << std::string(indent, ' ');
        }

        std::cout << node->getKey() << " (" << (node->color == RED ? "R" : "B") << ")" << std::endl;

        printTree(node->left, indent + 4);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::print() const {
    printTree(root);
}
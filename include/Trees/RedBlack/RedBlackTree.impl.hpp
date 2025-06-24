#include "Trees/RedBlack/RedBlackTree.hpp"

template <typename Key, typename Value>
const RedBlackNode<Key, Value>* RedBlackTree<Key, Value>::getRoot() const {
    return root;
}

template <typename Key, typename Value>
RedBlackNode<Key, Value>* RedBlackTree<Key, Value>::rotateLeft(RedBlackNode<Key, Value>* y) {
	RedBlackNode<Key, Value>* x = y->right;

	y->right = x->left;
    if (y->right != NIL) y->right->parent = y;
	x->left = y;

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
RedBlackNode<Key, Value>* RedBlackTree<Key, Value>::rotateRight(RedBlackNode<Key, Value>* y) {
	RedBlackNode<Key, Value>* x = y->left;

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
void RedBlackTree<Key, Value>::insertFixup(RedBlackNode<Key, Value>* z) {
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
RedBlackNode<Key, Value>* const RedBlackTree<Key, Value>::NIL = new RedBlackNode<Key, Value>(
    Key(), Value(), NIL, NIL, NIL, BLACK
);

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() {
    root = NIL;
    comparisonsCount = 0;
    maxKeyLen = 0;
    maxValLen = 0;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    this->setMaxKeyLen(key);
	maxValLen = std::max(maxValLen, StringHandler::size(value));

    RedBlackNode<Key, Value> *z = new RedBlackNode<Key, Value>(key, value, NIL, NIL, NIL, RED);

    RedBlackNode<Key, Value> *x = root, *y = NIL;
    
    while (x != NIL) {
        y = x;

        this->incrementCounter();
        if (z->getKey() < x->getKey()) {
            x = x->left;
        } else if (z->getKey() > x->getKey()) {
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
void RedBlackTree<Key,Value>::deleteFixup(RedBlackNode<Key, Value>* x) {
    while (x != root and x->color == BLACK) {
        if (x == x->parent->left) {
            RedBlackNode<Key, Value>* w = x->parent->right;

            if (w->color == RED) { // Case 1
                x->parent->color = RED;
                w->color = BLACK;
                x->parent = rotateLeft(x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK and w->right->color == BLACK) { // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) { // Case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    w = rotateRight(w);
                    w = x->parent->right;
                }

                // Case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                w = rotateLeft(x->parent);

                x = root;
            }
        } else { // Symetrical case
            RedBlackNode<Key, Value>* w = x->parent->left;

            if (w->color == RED) { // Case 1
                x->parent->color = RED;
                w->color = BLACK;
                x->parent = rotateRight(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK and w->left->color == BLACK) { // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) { // Case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    w = rotateLeft(w);
                    w = x->parent->left;
                }

                // Case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                w = rotateRight(x->parent);

                x = root;
            }
        }
    }

    x->color = BLACK;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::deleteNode(RedBlackNode<Key, Value>* z) {
    RedBlackNode<Key, Value>* y;
    if (z->left == NIL or z->right == NIL)
        y = z;
    else
        y = this->minimum(z->right);
    
    RedBlackNode<Key, Value>* x;
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if (y->parent == NIL) {
        root = x;
    } else {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y != z)
        y->setKey(z->getKey());

    if (y->color == BLACK)
        deleteFixup(x);

    delete y;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::printTree(RedBlackNode<Key, Value>* node, int indent) const {
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
bool RedBlackTree<Key, Value>::find(const Key& key, Value& outValue) {
    const RedBlackNode<Key, Value>* node = this->findNode(key);
    
    if (!node) return false;

    outValue = node->getValue();
    return true;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::update(const Key& key, const Value& value) {
    RedBlackNode<Key, Value>* aux = root;
    while (aux != NIL) {
        this->incrementCounter();
        
        if (key < aux->getKey()) {
            aux = aux->left;
        } else if (key > aux->getKey()) {
            aux = aux->right;
        } else {
            aux->setValue(value);
            return;
        }
    }

    throw KeyNotFoundException();
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::print() const {
    printTree(root);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(const Key& key) {
    RedBlackNode<Key, Value>* p = root;

    while (p != NIL and p->getKey() != key) {
        if (key < p->getKey()) p = p->left;
        else p = p->right;
    }

    if (p != NIL)
        deleteNode(p);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::clear() {
    this->clearNode(root, NIL);
    root = NIL;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::printInOrder(std::ostream& os) const {
    this->inOrderTransversal(os, root, NIL);
}

template <typename Key, typename Value>
size_t RedBlackTree<Key, Value>::getComparisonsCount() const {
    return comparisonsCount;
}

template <typename Key, typename Value>
Value& RedBlackTree<Key, Value>::operator[](const Key& key) {
    this->setMaxKeyLen(key);

    RedBlackNode<Key, Value> *x = root, *y = NIL;
    
    while (x != NIL) {
        y = x;

        this->incrementCounter();
        if (key < x->getKey()) {
            x = x->left;
        } else if (key > x->getKey()) {
            x = x->right;
        } else {
            this->setMaxValLen(x->getValue());        
            return x->getValue();
        }
    }

    RedBlackNode<Key, Value> *z = new RedBlackNode<Key, Value>(key, Value(), NIL, NIL, NIL, RED);

    this->setMaxValLen(z->getValue());

    z->parent = y;
    if (y == NIL) 
        root = z;
    else if (z->getKey() < y->getKey())
        y->left = z;
    else
        y->right = z;

    this->incrementCounter();

    insertFixup(z);

    return z->getValue();
}

template <typename Key, typename Value>
const Value& RedBlackTree<Key, Value>::operator[](const Key& key) const {
    return this->at(key);
}
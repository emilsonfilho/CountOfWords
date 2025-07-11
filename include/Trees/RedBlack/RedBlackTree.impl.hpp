#include "Trees/RedBlack/RedBlackTree.hpp"

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateLeft(RedBlackNode<Key, Value> *x) {
  RedBlackNode<Key, Value> *y = x->right;

  x->right = y->left;

  if (y->left != NIL)
    y->left->parent = x;
  
  y->parent = x->parent;

  if (x->parent == NIL)
    this->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;

  this->incrementRotationsCount();
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateRight(RedBlackNode<Key, Value> *x) {
  RedBlackNode<Key, Value> *y = x->left;

  x->left = y->right;

  if (y->right != NIL)
    y->right->parent = x;
  
  y->parent = x->parent;

  if (x->parent == NIL)
    this->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;

  this->incrementRotationsCount();
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insertFixup(RedBlackNode<Key, Value> *z) {
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
          rotateLeft(z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateRight(z->parent->parent);
      }
    } else {                                       // Symmetrical case
      if (z->parent->parent->left->color == RED) { // Case 1
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        z->parent->parent->left->color = BLACK;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) { // Case 2
          z = z->parent;
          rotateRight(z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateLeft(z->parent->parent);
      }
    }
  }

  this->root->color = BLACK;
}

template <typename Key, typename Value>
RedBlackNode<Key, Value> RedBlackTree<Key, Value>::NIL_NODE =
    RedBlackNode<Key, Value>();

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree()
    : BaseTree<RedBlackTree<Key, Value>, RedBlackNode<Key, Value>, Key, Value>(
          NIL) {}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key &key, const Value &value) {
  RedBlackNode<Key, Value> *x = this->root, *y = NIL;

  while (x != NIL) {
    y = x;

    if (key < x->getKey()) {
      this->incrementCounter(1);
      x = x->left;
    } else if (key > x->getKey()) {
      this->incrementCounter(2);
      x = x->right;
    } else {
      this->incrementCounter(2);
      throw KeyAlreadyExistsException();
    }
  }

  this->setMaxKeyLen(key);
  this->setMaxValLen(value);

  RedBlackNode<Key, Value> *z =
      new RedBlackNode<Key, Value>(key, value, NIL, NIL, NIL, RED);

  z->parent = y;
  if (y == NIL) {
    this->incrementCounter(1);
    this->root = z;
  } else if (z->getKey() < y->getKey()) {
    this->incrementCounter(2);
    y->left = z;
  } else {
    this->incrementCounter(2);
    y->right = z;
  }

  insertFixup(z);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::deleteFixup(RedBlackNode<Key, Value> *x) {
  while (x != this->root and x->color == BLACK) {
    if (x == x->parent->left) {
      RedBlackNode<Key, Value> *w = x->parent->right;

      if (w->color == RED) { // Case 1
        x->parent->color = RED;
        w->color = BLACK;
        rotateLeft(x->parent);
      }

      if (w->left->color == BLACK and w->right->color == BLACK) { // Case 2
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) { // Case 3
          w->left->color = BLACK;
          w->color = RED;
          rotateRight(w);
        }

        // Case 4
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rotateLeft(x->parent);

        x = this->root;
      }
    } else { // Symetrical case
      RedBlackNode<Key, Value> *w = x->parent->left;

      if (w->color == RED) { // Case 1
        x->parent->color = RED;
        w->color = BLACK;
        rotateRight(x->parent);
      }

      if (w->right->color == BLACK and w->left->color == BLACK) { // Case 2
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) { // Case 3
          w->right->color = BLACK;
          w->color = RED;
          rotateLeft(w);
        }

        // Case 4
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rotateRight(x->parent);

        x = this->root;
      }
    }
  }

  x->color = BLACK;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::deleteNode(RedBlackNode<Key, Value> *z) {
  RedBlackNode<Key, Value> *y;
  if (z->left == NIL or z->right == NIL)
    y = z;
  else
    y = this->minimum(z->right);

  RedBlackNode<Key, Value> *x;
  if (y->left != NIL)
    x = y->left;
  else
    x = y->right;

  x->parent = y->parent;

  if (y->parent == NIL) {
    this->root = x;
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
void RedBlackTree<Key, Value>::printTree(RedBlackNode<Key, Value>* node,
                                         const std::string& prefix,
                                         bool isLeft) const {
    if (node == this->NIL) return;

    std::cout << prefix;

    std::cout << (isLeft ? "├── " : "└── ");

    std::cout << node->getKey() << " (" << (node->color == RED ? "R" : "B") << ")" << std::endl;

    std::string newPrefix = prefix + (isLeft ? "│   " : "    ");
    bool hasLeft = node->left != this->NIL;
    bool hasRight = node->right != this->NIL;

    if (hasRight)
        printTree(node->right, newPrefix, true);
    if (hasLeft)
        printTree(node->left, newPrefix, false);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::print() const {
    if (this->root == this->NIL) {
        std::cout << "Árvore vazia.\n";
        return;
    }

    std::cout << this->root->getKey() << " (" << (this->root->color == RED ? "R" : "B") << ") (Raiz)\n";
    bool hasRight = this->root->right != this->NIL;
    bool hasLeft = this->root->left != this->NIL;

    if (hasRight)
        printTree(this->root->right, "", true);
    if (hasLeft)
        printTree(this->root->left, "", false);
}



template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::find(const Key &key, Value &outValue) const {
  const RedBlackNode<Key, Value> *node = this->findNode(key, NIL);

  if (!node)
    return false;

  outValue = node->getValue();
  return true;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::update(const Key &key, const Value &value) {
  RedBlackNode<Key, Value> *aux = this->root;
  while (aux != NIL) {
    if (key < aux->getKey()) {
      this->incrementCounter(1);
      aux = aux->left;
    } else if (key > aux->getKey()) {
      this->incrementCounter(2);
      aux = aux->right;
    } else {
      this->incrementCounter(2);
      aux->setValue(value);
      return;
    }
  }

  throw KeyNotFoundException();
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(const Key &key) {
  RedBlackNode<Key, Value> *p = this->root;

  while (p != NIL and p->getKey() != key) {
    if (key < p->getKey())
      p = p->left;
    else
      p = p->right;

    this->incrementCounter(1);
  }

  if (p != NIL)
    deleteNode(p);
}

template <typename Key, typename Value> void RedBlackTree<Key, Value>::clear() {
  this->reset(this->root, NIL, NIL);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::printInOrder(std::ostream &os) const {
  this->inOrderTransversal(os, this->root, NIL);
}

template <typename Key, typename Value>
size_t RedBlackTree<Key, Value>::getComparisonsCount() const {
  return this->comparisonsCount;
}

template <typename Key, typename Value>
Value &RedBlackTree<Key, Value>::operator[](const Key &key) {
  this->setMaxKeyLen(key);

  RedBlackNode<Key, Value> *x = this->root, *y = NIL;

  while (x != NIL) {
    y = x;

    if (key < x->getKey()) {
      this->incrementCounter(1);
      x = x->left;
    } else if (key > x->getKey()) {
      this->incrementCounter(2);
      x = x->right;
    } else {
      this->incrementCounter(2);
      this->setMaxValLen(x->getValue());
      return x->getValue();
    }
  }

  RedBlackNode<Key, Value> *z =
      new RedBlackNode<Key, Value>(key, Value(), NIL, NIL, NIL, RED);

  this->setMaxValLen(z->getValue());

  z->parent = y;
  if (y == NIL) {
    this->incrementCounter(1);
    this->root = z;
  } else if (z->getKey() < y->getKey()) {
    this->incrementCounter(2);
    y->left = z;
  } else {
    this->incrementCounter(2);
    y->right = z;
  }

  insertFixup(z);

  return z->getValue();
}

template <typename Key, typename Value>
const Value &RedBlackTree<Key, Value>::operator[](const Key &key) const {
  return this->at(key);
}

template <typename Key, typename Value>
size_t RedBlackTree<Key, Value>::getRotationsCount() const {
  return this->rotationsCount;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::accept(
    IDictionaryVisitor<Key, Value> &visitor) const {
  visitor.collectMetrics(*this);
}

template <typename Key, typename Value>
size_t RedBlackTree<Key, Value>::getMemoryUsage() const {
  return this->sizeOf(NIL);
}
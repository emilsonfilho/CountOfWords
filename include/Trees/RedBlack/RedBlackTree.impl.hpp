#include "Trees/RedBlack/RedBlackTree.hpp"

template <typename Key, typename Value>
RedBlackNode<Key, Value> *
RedBlackTree<Key, Value, Compare>::rotateLeft(RedBlackNode<Key, Value> *y) {
  RedBlackNode<Key, Value> *x = y->right;

  y->right = x->left;
  if (y->right != NIL)
    y->right->parent = y;
  x->left = y;

  x->parent = y->parent;
  y->parent = x;

  if (x->parent != NIL) {
    if (x->getKey() < x->parent->getKey())
      x->parent->left = x;
    else
      x->parent->right = x;
  } else {
    this->root = x;
  }

  this->incrementRotationsCount();

  return x;
}

template <typename Key, typename Value>
RedBlackNode<Key, Value> *
RedBlackTree<Key, Value, Compare>::rotateRight(RedBlackNode<Key, Value> *y) {
  RedBlackNode<Key, Value> *x = y->left;

  y->left = x->right;
  if (y->left != NIL)
    y->left->parent = y;
  x->right = y;

  x->parent = y->parent;
  y->parent = x;

  if (x->parent != NIL) {
    if (x->getKey() < x->parent->getKey())
      x->parent->left = x;
    else
      x->parent->right = x;
  } else {
    this->root = x;
  }

  this->incrementRotationsCount();

  return x;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::insertFixup(RedBlackNode<Key, Value> *z) {
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
    } else {                                       // Symmetrical case
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

  this->root->color = BLACK;
}

template <typename Key, typename Value>
RedBlackNode<Key, Value> RedBlackTree<Key, Value, Compare>::NIL_NODE =
    RedBlackNode<Key, Value>();

template <typename Key, typename Value>
RedBlackTree<Key, Value, Compare>::RedBlackTree()
    : BaseTree<RedBlackTree<Key, Value, Compare>, RedBlackNode<Key, Value>, Key, Value>(
          NIL) {}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::insert(const Key &key, const Value &value) {
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
void RedBlackTree<Key, Value, Compare>::deleteFixup(RedBlackNode<Key, Value> *x) {
  while (x != this->root and x->color == BLACK) {
    if (x == x->parent->left) {
      RedBlackNode<Key, Value> *w = x->parent->right;

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

        x = this->root;
      }
    } else { // Symetrical case
      RedBlackNode<Key, Value> *w = x->parent->left;

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

        x = this->root;
      }
    }
  }

  x->color = BLACK;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::deleteNode(RedBlackNode<Key, Value> *z) {
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
void RedBlackTree<Key, Value, Compare>::printTree(RedBlackNode<Key, Value> *node,
                                         int indent) const {
  if (node != NIL) {
    printTree(node->right, indent + 4);

    if (indent > 0) {
      std::cout << std::string(indent, ' ');
    }

    std::cout << node->getKey() << " (" << (node->color == RED ? "R" : "B")
              << ")" << std::endl;

    printTree(node->left, indent + 4);
  }
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value, Compare>::find(const Key &key, Value &outValue) const {
  const RedBlackNode<Key, Value> *node = this->findNode(key, NIL);

  if (!node)
    return false;

  outValue = node->getValue();
  return true;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::update(const Key &key, const Value &value) {
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
void RedBlackTree<Key, Value, Compare>::print() const {
  printTree(this->root);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::remove(const Key &key) {
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

template <typename Key, typename Value> void RedBlackTree<Key, Value, Compare>::clear() {
  this->reset(this->root, NIL, NIL);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::printInOrder(std::ostream &os) const {
  this->inOrderTransversal(os, this->root, NIL);
}

template <typename Key, typename Value>
size_t RedBlackTree<Key, Value, Compare>::getComparisonsCount() const {
  return this->comparisonsCount;
}

template <typename Key, typename Value>
Value &RedBlackTree<Key, Value, Compare>::operator[](const Key &key) {
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
const Value &RedBlackTree<Key, Value, Compare>::operator[](const Key &key) const {
  return this->at(key);
}

template <typename Key, typename Value>
size_t RedBlackTree<Key, Value, Compare>::getRotationsCount() const {
  return this->rotationsCount;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value, Compare>::accept(
    IDictionaryVisitor<Key, Value> &visitor) const {
  visitor.collectMetrics(*this);
}
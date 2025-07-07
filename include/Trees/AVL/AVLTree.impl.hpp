#include "Trees/AVL/AVLTree.hpp"

#include <cmath>
#include <iostream>

#include "Utils/Strings/StringHandler.hpp"

template <typename Key, typename Value, typename Compare>
size_t AVLTree<Key, Value, Compare>::height(AVLNode<Key, Value> *node) const {
  if (!node)
    return 0;

  return node->height;
}

template <typename Key, typename Value, typename Compare>
size_t AVLTree<Key, Value, Compare>::calcHeight(AVLNode<Key, Value> *node) const {
  if (!node)
    return 0;

  size_t leftHeight = height(node->left), rightHeight = height(node->right);

  return 1 + std::max(leftHeight, rightHeight);
}

template <typename Key, typename Value, typename Compare>
int AVLTree<Key, Value, Compare>::getBalanceFactor(AVLNode<Key, Value> *node) const {
  if (!node)
    return 0;
  return height(node->right) - height(node->left);
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::rotateLeft(AVLNode<Key, Value> *&y) {
  AVLNode<Key, Value> *x = y->right;

  y->right = x->left;
  x->left = y;

  y->height = calcHeight(y);
  x->height = calcHeight(x);

  this->incrementRotationsCount();

  return x;
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::rotateRight(AVLNode<Key, Value> *&y) {
  AVLNode<Key, Value> *x = y->left;

  y->left = x->right;
  x->right = y;

  y->height = calcHeight(y);
  x->height = calcHeight(x);

  this->incrementRotationsCount();

  return x;
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::fixupNode(AVLNode<Key, Value> *y) {
  if (!y)
    return nullptr;

  int balanceFactor = getBalanceFactor(y);

  if (std::abs(balanceFactor) == IMBALANCE) {
    if (balanceFactor < 0) {
      if (getBalanceFactor(y->left) <= 0) {
        y = rotateRight(y);

      } else {
        y->left = rotateLeft(y->left);
        y = rotateRight(y);
      }
    } else {
      if (getBalanceFactor(y->right) >= 0) {
        y = rotateLeft(y);

      } else {
        y->right = rotateRight(y->right);
        y = rotateLeft(y);
      }
    }
  }

  y->height = calcHeight(y);

  return y;
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *
AVLTree<Key, Value, Compare>::removeSuccessor(AVLNode<Key, Value> *root,
                                     AVLNode<Key, Value> *node) {
  if (node->left) {
    node->left = removeSuccessor(root, node->left);
  } else {
    root->setKey(node->getKey());
    root->setValue(node->getValue());
    AVLNode<Key, Value> *aux = node->right;
    delete node;
    return aux;
  }

  return fixupNode(node);
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::insert(const Key &key,
                                                 const Value &value,
                                                 AVLNode<Key, Value> *node) {
  // It'll never be called w/ root == nullptr
  if (!node)
    return new AVLNode(key, value);

  if (this->isLeft(key, node->getKey())) {
    this->incrementCounter(1);
    node->left = insert(key, value, node->left);
  } else if (this->isRight(key, node->getKey())) {
    this->incrementCounter(2);
    node->right = insert(key, value, node->right);
  } else {
    this->incrementCounter(2);
    throw KeyAlreadyExistsException();
  }

  return fixupNode(node);
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::update(const Key &key,
                                                 const Value &value,
                                                 AVLNode<Key, Value> *node) {
  if (!node)
    throw KeyNotFoundException();

  if (this->isLeft(key, node->getKey())) {
    this->incrementCounter(1);
    node->left = update(key, value, node->left);
  } else if (this->isRight(key, node->getKey())) {
    this->incrementCounter(2);
    node->right = update(key, value, node->right);
  } else {
    this->incrementCounter(2);
    node->setValue(value);
  }

  return fixupNode(node);
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::remove(const Key &key,
                                                 AVLNode<Key, Value> *node) {
  if (!node)
    return nullptr;

  if (this->isLeft(key, node->getKey())) {
    node->left = remove(key, node->left);
  } else if (this->isRight(key, node->getKey())) {
    node->right = remove(key, node->right);
  } else if (!node->right) {
    AVLNode<Key, Value> *leftChild = node->left;
    delete node;
    return leftChild;
  } else {
    node->right = removeSuccessor(node, node->right);
  }

  return fixupNode(node);
}

template <typename Key, typename Value, typename Compare>
AVLNode<Key, Value> *AVLTree<Key, Value, Compare>::upsert(const Key &key,
                                                 AVLNode<Key, Value> *node,
                                                 Value *&outValue) {
  this->setMaxKeyLen(key);

  if (!node) {
    AVLNode<Key, Value> *newNode = new AVLNode<Key, Value>(key, Value());
    outValue = &(newNode->getValue());
    this->setMaxValLen(*outValue);
    return newNode;
  }

  if (this->isLeft(key, node->getKey())) {
    this->incrementCounter(1);
    node->left = upsert(key, node->left, outValue);
  } else if (this->isRight(key, node->getKey())) {
    this->incrementCounter(2);
    node->right = upsert(key, node->right, outValue);
  } else {
    this->incrementCounter(2);
    outValue = &(node->getValue());
    this->setMaxValLen(*outValue);
    return node;
  }

  return fixupNode(node);
}

template <typename Key, typename Value, typename Compare>
AVLTree<Key, Value, Compare>::AVLTree()
    : BaseTree<AVLTree<Key, Value, Compare>, AVLNode<Key, Value>, Key, Value>(nullptr) {}

template <typename Key, typename Value, typename Compare> AVLTree<Key, Value, Compare>::~AVLTree() {
  clear();
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::insert(const Key &key, const Value &value) {
  this->root = insert(key, value, this->root);
  this->setMaxKeyLen(key);
  this->setMaxValLen(value);
}

template <typename Key, typename Value, typename Compare>
bool AVLTree<Key, Value, Compare>::find(const Key &key, Value &outValue) const {
  const AVLNode<Key, Value> *node = this->findNode(key);

  if (!node)
    return false;

  outValue = node->getValue();
  return true;
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::update(const Key &key, const Value &value) {
  this->root = update(key, value, this->root);
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::remove(const Key &key) {
  this->root = remove(key, this->root);
}

template <typename Key, typename Value, typename Compare> void AVLTree<Key, Value, Compare>::clear() {
  this->reset(this->root);
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::printTree(AVLNode<Key, Value> *node,
                                    size_t depth) const {
  if (!node)
    return;

  printTree(node->right, depth + 1);

  for (int i = 0; i < depth; i++)
    std::cout << "    ";
  std::cout << node->show() << std::endl;

  printTree(node->left, depth + 1);
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::print() const {
  printTree(this->root);
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::printInOrder(std::ostream &os) const {
  this->inOrderTransversal(os, this->root, nullptr);
}

template <typename Key, typename Value, typename Compare>
size_t AVLTree<Key, Value, Compare>::getComparisonsCount() const {
  return this->comparisonsCount;
}

template <typename Key, typename Value, typename Compare>
Value &AVLTree<Key, Value, Compare>::operator[](const Key &key) {
  Value *insertedValue = nullptr;
  this->root = upsert(key, this->root, insertedValue);
  return *insertedValue;
}

template <typename Key, typename Value, typename Compare>
const Value &AVLTree<Key, Value, Compare>::operator[](const Key &key) const {
  return this->at(key);
}

template <typename Key, typename Value, typename Compare>
size_t AVLTree<Key, Value, Compare>::getRotationsCount() const {
  return this->rotationsCount;
}

template <typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::accept(
    IDictionaryVisitor<Key, Value> &visitor) const {
  visitor.collectMetrics(*this);
}
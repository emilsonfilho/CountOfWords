#ifndef BASE_TREE_IMPL_HPP
#define BASE_TREE_IMPL_HPP

#include "Trees/Base/BaseTree.hpp"

#include <cmath>

#include "Utils/Strings/StringHandler.hpp"

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::count(size_t n) const {
  static_cast<const Tree *>(this)->incrementCounter(n);
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::clearCounter() {
  static_cast<Tree *>(this)->resetCounter();
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
BaseTree<Tree, Node, Key, Value, Compare>::BaseTree(Node *r)
    : root(r), maxKeyLen(0), maxValLen(0), rotationsCount(0) {
  clearCounter();
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
const Node *BaseTree<Tree, Node, Key, Value, Compare>::findNode(const Key &key,
                                                       Node *comp) const {
  const Node *aux = root;

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

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
Node *BaseTree<Tree, Node, Key, Value, Compare>::minimum(Node *node) const {
  if (!node->left)
    return node;
  return minimum(node->left);
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::clearNode(Node *node, Node *comp) {
  if (node != comp) {
    clearNode(node->left, comp);
    clearNode(node->right, comp);
    delete node;
  }
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::reset(Node *node, Node *comp,
                                             Node *defaultRoot) {
  clearNode(node, comp);
  root = defaultRoot;
  maxKeyLen = 0;
  maxValLen = 0;
  rotationsCount = 0;
  clearCounter();
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::inOrderTransversal(std::ostream &out,
                                                          Node *node,
                                                          Node *comp) const {
  if (node != comp) {
    inOrderTransversal(out, node->left, comp);

    out << StringHandler::SetWidthAtLeft(node->getKey(), maxKeyLen) << " | "
        << StringHandler::SetWidthAtLeft(node->getValue(), maxValLen) << '\n';

    inOrderTransversal(out, node->right, comp);
  }
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
const Value &BaseTree<Tree, Node, Key, Value, Compare>::at(const Key &key,
                                                  Node *comp) const {
  const Node *aux = root;

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

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::setMaxKeyLen(const Key &key) {
  maxKeyLen = std::max(maxKeyLen, StringHandler::size(key));
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::setMaxValLen(const Value &value) {
  maxValLen = std::max(maxValLen, StringHandler::size(value));
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
void BaseTree<Tree, Node, Key, Value, Compare>::incrementRotationsCount(size_t amount) {
  rotationsCount += amount;
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
bool BaseTree<Tree, Node, Key, Value, Compare>::isLeft(const Key& a, const Key& b) const {
  return comp(a, b);
}

template <typename Tree, typename Node, typename Key, typename Value, typename Compare>
bool BaseTree<Tree, Node, Key, Value, Compare>::isRight(const Key& a, const Key& b) const {
  return comp(b, a);
}

#endif

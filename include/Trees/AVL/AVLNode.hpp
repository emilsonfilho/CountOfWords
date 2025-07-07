#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

#include "Trees/Base/Node.hpp"

/**
 * @brief AVL tree node structure extending a generic Node.
 *
 * @tparam Key The type of the key.
 * @tparam Value The type of the value.
 */
template <typename Key, typename Value>
struct AVLNode : public Node<Key, Value> {
  /**
   * @brief Pointer to the left child.
   */
  AVLNode *left;

  /**
   * @brief Pointer to the right child.
   */
  AVLNode *right;

  /**
   * @brief Height of the node in the AVL tree.
   */
  size_t height;

  /**
   * @brief Constructs a Node object with the given key and value.
   *
   * @param k The key associated with the node.
   * @param v The value associated with the node.
   */
  AVLNode(const Key &k, const Value &v)
      : Node<Key, Value>(k, v), left(nullptr), right(nullptr), height(1) {}
};

#endif

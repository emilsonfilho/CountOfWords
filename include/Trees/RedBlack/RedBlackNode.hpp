#ifndef RED_BLACK_NODE_HPP
#define RED_BLACK_NODE_HPP

#include "Trees/Base/Node.hpp"
#include "Trees/RedBlack/Color.hpp"

template <typename Key, typename Value>
struct RedBlackNode : public Node<Key, Value> {
  /**
   * @brief Pointer to the left child node in the Red-Black Tree.
   *
   * This pointer references the left child of the current node.
   * It is used to traverse the tree structure and maintain the
   * Red-Black Tree properties.
   */
  RedBlackNode *left;

  /**
   * @brief Pointer to the right child node in the Red-Black Tree.
   *
   * This pointer references the right child of the current node. It is used
   * to traverse or manipulate the right subtree of the Red-Black Tree.
   */
  RedBlackNode *right;

  /**
   * @brief Pointer to the parent node in the Red-Black Tree.
   *
   * This pointer is used to maintain the hierarchical relationship
   * between nodes in the Red-Black Tree. It points to the parent
   * of the current node, or is set to nullptr if the current node
   * is the root of the tree.
   */
  RedBlackNode *parent;

  /**
   * @brief Represents the color of a node in a Red-Black Tree.
   *
   * The color can typically be either RED or BLACK, and it is used to
   * maintain the balancing properties of the Red-Black Tree.
   */
  Color color;

  /**
   * @brief Constructs a RedBlackNode.
   *
   * @param k The key for the node.
   * @param v The value for the node.
   * @param l Pointer to the left child node.
   * @param r Pointer to the right child node.
   * @param p Pointer to the parent node.
   * @param c The color of the node (Red or Black).
   */
  RedBlackNode(const Key &k, const Value &v, RedBlackNode *l, RedBlackNode *r,
               RedBlackNode *p, Color c)
      : Node<Key, Value>(k, v), left(l), right(r), parent(p), color(c) {}

  /**
   * @class RedBlackNode
   * @brief Represents a node in a Red-Black Tree.
   *
   * This class extends the generic Node class and includes additional
   * properties specific to Red-Black Trees, such as color and self-referencing
   * pointers for left, right, and parent nodes.
   *
   * @param color The color of the node, either RED or BLACK. Defaults to BLACK.
   *
   * The constructor initializes the node with default key and value, and sets
   * the left, right, and parent pointers to point to itself. This is useful for
   * representing sentinel nodes (e.g., NIL nodes) in a Red-Black Tree.
   */
  RedBlackNode(Color color = BLACK) : Node<Key, Value>(Key(), Value()) {
    this->left = this;
    this->right = this;
    this->parent = this;
    this->color = color;
  }
};

#endif
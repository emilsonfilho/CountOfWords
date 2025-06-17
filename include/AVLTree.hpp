#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class AVLTree: public Dictionary {
    class Node {
        std::pair<Key, Value> data;
        Node *left, *right;
        int height;
    }
private:
    /* data */
    Node* root;
    int comparisonsCount;
public:
    AVLTree();
    ~AVLTree();
};

AVLTree::AVLTree(/* args */) {}

AVLTree::~AVLTree() {}

#endif

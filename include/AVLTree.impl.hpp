#include "AVLTree.hpp"

#include <iostream>
#include <cmath>

#include "utils/Utils.hpp"

template <typename Key, typename Value, typename Hash>
AVLTree<Key, Value, Hash>::Node::Node(const Key& k, const Value& v): data({k, v}), left(nullptr), right(nullptr), height(1) {}

template <typename Key, typename Value, typename Hash>
AVLTree<Key, Value, Hash>::AVLTree(): root(nullptr), comparisonsCount(0) {}

template <typename Key, typename Value, typename Hash>
typename AVLTree<Key, Value, Hash>::Node* AVLTree<Key, Value, Hash>::rotateLeft(Node*& y) {
	Node* x = y->right;

	y->right = x->left;
	x->left = y;

	y->height = calcHeight(y);
	x->height = calcHeight(x);

	return x;
}

template <typename Key, typename Value, typename Hash>
typename AVLTree<Key, Value, Hash>::Node* AVLTree<Key, Value, Hash>::rotateRight(Node*& y) {
	Node* x = y->left;

	y->left = x->right;
	x->right = y;

	y->height = calcHeight(y);
	x->height = calcHeight(x);

	return x;
}

template <typename Key, typename Value, typename Hash>
typename AVLTree<Key, Value, Hash>::Node* AVLTree<Key, Value, Hash>::fixupNode(Node* y) {
	if (!y) return nullptr;

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

template <typename Key, typename Value, typename Hash>
typename AVLTree<Key, Value, Hash>::Node* AVLTree<Key, Value, Hash>::insert(const Key& key, const Value& value, Node* node) {
	// It'll never be called w/ root == nullptr
	if (!node)
		return new Node(key, value);

	if (key < node->data.first) {
		node->left = insert(key, value, node->left);
	} else if (key > node->data.first) {
		node->right = insert(key, value, node->right);
	} else {
		node->data.first = key;
		return node;
	}

	return fixupNode(node);
}

template  <typename Key, typename Value, typename Hash>
bool AVLTree<Key, Value, Hash>::find(const Key& key, Value& outValue, Node* node) {
	if (!node) return false;

	if (key < node->data.first) {
		comparisonsCount++;
		return find(key, outValue, node->left);
	} else if (key > node->data.first) {
		comparisonsCount++;
		return find(key, outValue, node->right);
	}

	outValue = node->data.second;
	comparisonsCount++;
	return true;
}

template <typename Key, typename Value, typename Hash>
typename AVLTree<Key, Value, Hash>::Node* AVLTree<Key, Value, Hash>::update(const Key& key, const Value& value, Node* node) {
	if (!node) return new Node(key, value);

	if (key < node->data.first) {
		node->left = update(key, value, node->left);
	} else if (key > node->data.first) {
		node->right = update(key, value, node->right);
	} else {
		node->data.second = value;
	}

	return fixupNode(node);
}

template <typename Key, typename Value, typename Hash>
void AVLTree<Key, Value, Hash>::insert(const Key& key, const Value& value) {
	root = insert(key, value, root);
}

template  <typename Key, typename Value, typename Hash>
bool AVLTree<Key, Value, Hash>::find(const Key& key, Value& outValue) {
	return find(key, outValue, root);
}

template <typename Key, typename Value, typename Hash>
void AVLTree<Key, Value, Hash>::update(const Key& key, const Value& value) {
	root = update(key, value, root);
}

template <typename Key, typename Value, typename Hash>
void AVLTree<Key, Value, Hash>::printTree(Node* node, size_t depth) const {
	if (!node) return;

	printTree(node->right, depth+1);

	for (int i = 0; i < depth; i++)
		std::cout << "    ";
	std::cout << Utils::displayPair(node->data) << std::endl;

	printTree(node->left, depth+1);
}

template <typename Key, typename Value, typename Hash>
void AVLTree<Key, Value, Hash>::print() const {
	printTree(root);
}
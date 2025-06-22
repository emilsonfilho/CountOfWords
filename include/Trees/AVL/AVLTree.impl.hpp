#include "Trees/AVL/AVLTree.hpp"

#include <iostream>
#include <cmath>

template <typename Key, typename Value>
const AVLNode<Key, Value>* AVLTree<Key, Value>::getRoot() const {
	return root;
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::height(AVLNode<Key, Value>* node) const {
	if (!node) return 0;

    return node->height;
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::calcHeight(AVLNode<Key, Value>* node) const {
    if (!node) return 0;

    size_t leftHeight = height(node->left),
           rightHeight = height(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::getBalanceFactor(AVLNode<Key, Value>* node) const {
    if (!node) return 0;
    return height(node->right) - height(node->left);
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>*& y) {
	AVLNode<Key, Value>* x = y->right;

	y->right = x->left;
	x->left = y;

	y->height = calcHeight(y);
	x->height = calcHeight(x);

	return x;
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>*& y) {
	AVLNode<Key, Value>* x = y->left;

	y->left = x->right;
	x->right = y;

	y->height = calcHeight(y);
	x->height = calcHeight(x);

	return x;
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixupNode(AVLNode<Key, Value>* y) {
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

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::removeSuccessor(AVLNode<Key, Value>* root, AVLNode<Key, Value>* node) {
	if (node->left) {
		node->left = removeSuccessor(root, node->left);
	} else {
		root->setKey(node->getKey());
		root->setValue(node->getValue());
		AVLNode<Key, Value>* aux = node->right;
		delete node;
		return aux;
	}

	return fixupNode(node);
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insert(const Key& key, const Value& value, AVLNode<Key, Value>* node) {
	// It'll never be called w/ root == nullptr
	if (!node)
		return new AVLNode(key, value);

	if (key < node->getKey()) {
		node->left = insert(key, value, node->left);
	} else if (key > node->getKey()) {
		node->right = insert(key, value, node->right);
	} else {
		throw KeyAlreadyExistsException();
	}

	this->incrementCounter();

	return fixupNode(node);
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::update(const Key& key, const Value& value, AVLNode<Key, Value>* node) {
	if (!node) throw KeyNotFoundException();

	if (key < node->getKey()) {
		node->left = update(key, value, node->left);
	} else if (key > node->getKey()) {
		node->right = update(key, value, node->right);
	} else {
		node->setValue(value);
	}

	this->incrementCounter();

	return fixupNode(node);
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::remove(const Key& key, AVLNode<Key, Value>* node) {
	if (!node) return nullptr;

	if (key < node->getKey()) {
		node->left = remove(key, node->left);
	} else if (key > node->getKey()) {
		node->right = remove(key, node->right);
	} else if (!node->right) {
		AVLNode<Key, Value>* leftChild = node->left;
		delete node;
		return leftChild;
	} else {
		node->right = removeSuccessor(node, node->right);
	}

	return fixupNode(node);
}

template <typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::upsert(const Key& key, AVLNode<Key, Value>* node, Value*& outValue) {
	if (!node) {
		AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(key, Value());
		outValue = &(newNode->getValue());
		return newNode;
	}

	this->incrementCounter();

	if (key < node->getKey()) {
		node->left = upsert(key, node->left, outValue);
	} else if (key > node->getKey()) {
		node->right = upsert(key, node->right, outValue);
	} else {
		outValue = &(node->getValue());
		return node;
	}

	return fixupNode(node);
}

template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(): root(nullptr) {}

template <typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() { clear(); }

template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const Key& key, const Value& value) {
	root = insert(key, value, root);
}

template  <typename Key, typename Value>
bool AVLTree<Key, Value>::find(const Key& key, Value& outValue) {
	const AVLNode<Key, Value>* node = this->findNode(key);

	if (!node) return false;

	outValue = node->getValue();
	return true;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::update(const Key& key, const Value& value) {
	root = update(key, value, root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key) {
	root = remove(key, root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
	this->clearNode(root, nullptr);
	root = nullptr;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::printTree(AVLNode<Key, Value>* node, size_t depth) const {
	if (!node) return;

	printTree(node->right, depth+1);

	for (int i = 0; i < depth; i++)
		std::cout << "    ";
	std::cout << node->show() << std::endl;

	printTree(node->left, depth+1);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::print() const {
	printTree(root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::printInOrder(std::ostream& os) const {
	this->inOrderTransversal(os, root, nullptr);
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::getComparisonsCount() const {
	return this->comparisonsCount;
}

template <typename Key, typename Value>
Value& AVLTree<Key, Value>::operator[](const Key& key) {
	Value* insertedValue = nullptr;
	root = upsert(key, root, insertedValue);
	return *insertedValue;
}

template <typename Key, typename Value>
const Value& AVLTree<Key, Value>::operator[](const Key& key) const {
	return this->at(key);
}

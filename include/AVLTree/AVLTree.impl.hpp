#include "AVLTree/AVLTree.hpp"

#include <iostream>
#include <cmath>

#include "Exceptions/KeyExceptions.hpp"

template <typename Key, typename Value>
AVLTree<Key, Value>::AVLNode::AVLNode(const Key& k, const Value& v): Node<Key, Value>(k, v), left(nullptr), right(nullptr), height(1) {}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::height(AVLNode* node) const {
	if (!node) return 0;

    return node->height;
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::calcHeight(AVLNode* node) const {
    if (!node) return 0;

    size_t leftHeight = height(node->left),
           rightHeight = height(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::getBalanceFactor(AVLNode* node) const {
    if (!node) return 0;
    return height(node->right) - height(node->left);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::minimum(AVLNode* node) const {
    if (!node->left) return node;
    return minimum(node->left);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::rotateLeft(AVLNode*& y) {
	AVLNode* x = y->right;

	y->right = x->left;
	x->left = y;

	y->height = calcHeight(y);
	x->height = calcHeight(x);

	return x;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::rotateRight(AVLNode*& y) {
	AVLNode* x = y->left;

	y->left = x->right;
	x->right = y;

	y->height = calcHeight(y);
	x->height = calcHeight(x);

	return x;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::fixupNode(AVLNode* y) {
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
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::removeSuccessor(AVLNode* root, AVLNode* node) {
	if (node->left) {
		node->left = removeSuccessor(root, node->left);
	} else {
		root->setKey(node->getKey());
		root->setValue(node->getValue());
		AVLNode* aux = node->right;
		delete node;
		return aux;
	}

	return fixupNode(node);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::insert(const Key& key, const Value& value, AVLNode* node) {
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

template  <typename Key, typename Value>
bool AVLTree<Key, Value>::find(const Key& key, Value& outValue, AVLNode* node) {
	if (!node) return false;

	if (key < node->getKey()) {
		this->incrementCounter();
		return find(key, outValue, node->left);
	} else if (key > node->getKey()) {
		this->incrementCounter();
		return find(key, outValue, node->right);
	}

	outValue = node->getValue();
	this->incrementCounter();
	return true;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::update(const Key& key, const Value& value, AVLNode* node) {
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
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::remove(const Key& key, AVLNode* node) {
	if (!node) return nullptr;

	if (key < node->getKey()) {
		node->left = remove(key, node->left);
	} else if (key > node->getKey()) {
		node->right = remove(key, node->right);
	} else if (!node->right) {
		AVLNode* leftChild = node->left;
		delete node;
		return leftChild;
	} else {
		node->right = removeSuccessor(node, node->right);
	}

	return fixupNode(node);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear(AVLNode* node) {
	if (node) {
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::printInOrder(std::ostream& out, AVLNode* node) const {
	if (node) {
		printInOrder(out, node->left);

		out << node->show() << '\n';

		printInOrder(out, node->right);
	}
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
	return find(key, outValue, root);
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
	clear(root);
	root = nullptr;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::printTree(AVLNode* node, size_t depth) const {
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
	printInOrder(os, root);
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::getComparisonsCount() const {
	return this->comparisonsCount;
}

template <typename Key, typename Value>
Value& AVLTree<Key, Value>::operator[](const Key& key) {
	AVLNode** aux = &root;

	while (*aux) {
		if (key < (*aux)->getKey()) {
			this->incrementCounter();
			aux = &(*aux)->left;
		} else if (key > (*aux)->getKey()) {
			this->incrementCounter();
			aux = &(*aux)->right;
		} else {
			this->incrementCounter();
			return (*aux)->getValue();
		}
	}

	*aux = new AVLNode(key, Value());
	return (*aux)->getValue();
}

template <typename Key, typename Value>
const Value& AVLTree<Key, Value>::operator[](const Key& key) const {
	const AVLNode* aux = root;

	while (aux) {
		if (key < aux->getKey()) {
			this->incrementCounter();
			aux = aux->left;
		} else if (key > aux->getKey()) {
			this->incrementCounter();
			aux = aux->right;
		} else {
			this->incrementCounter();
			return aux->getValue();
		}
	}

	throw KeyNotFoundException();
}
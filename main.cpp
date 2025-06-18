#include "AVLTree.hpp"

int main() {
	AVLTree<std::string, int> avl;
	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);
	avl.insert("Miranda", 7);
	avl.insert("Karen", 5);
	avl.insert("Emilly", 6);
	avl.insert("Emanuel", 7);
	avl.print();

	return 0;
}
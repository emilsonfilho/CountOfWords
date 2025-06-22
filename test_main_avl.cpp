#include "Trees/AVL/AVLTree.hpp"
#include <iostream>
#include <cassert>

void testAVLInsertAndPrint() {
	AVLTree<std::string, int> avl;

	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);
	avl.insert("Miranda", 7);
	avl.insert("Karen", 5);
	avl.insert("Emilly", 6);
	avl.insert("Emanuel", 7);

	// Assuming printInOrder prints in sorted order
	std::cout << "AVL Tree after insertions (in-order):" << std::endl;
	avl.printInOrder(std::cout);
}

void testAVLRemove() {
	AVLTree<std::string, int> avl;

	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);
	avl.insert("Miranda", 7);
	avl.insert("Karen", 5);

	avl.remove("Miranda");

	std::cout << "AVL Tree after removing 'Miranda':" << std::endl;
	avl.printInOrder(std::cout);
}

void testAVLOperatorAccess() {
	AVLTree<std::string, int> avl;

	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);

	avl["Emilson"] = 10;
	avl["Jhon"] = 4;

	avl.print();

	assert(avl["Emilson"] == 10);
	assert(avl["Jhon"] == 4);

	std::cout << "AVL Tree after operator[] modifications:" << std::endl;
	avl.printInOrder(std::cout);
}

void testAVLFind() {
	AVLTree<std::string, int> avl;

	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);

	int out = 0;
	std::string name = "Mislayne";

	if (avl.find(name, out)) {
		std::cout << "Element " << name << " is in the tree? " << std::boolalpha << true << std::endl;
		std::cout << "Value: " << out << std::endl;
	} else {
		std::cout << "Element " << name << " is not in the tree" << std::endl;
	}
}

void testAVLComparisonsCount() {
	AVLTree<std::string, int> avl;

	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);
	avl.insert("Miranda", 7);

	
	std::cout << "Number of comparisons: " << avl.getComparisonsCount() << std::endl;
}

int main() {
	testAVLInsertAndPrint();
	testAVLRemove();
	testAVLOperatorAccess();
	testAVLFind();
	testAVLComparisonsCount();

	std::cout << "All AVL Tree tests completed successfully!" << std::endl;
	return 0;
}
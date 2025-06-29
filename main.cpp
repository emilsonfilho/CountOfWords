#include "Trees/RedBlack/RedBlackTree.hpp"
#include <iostream>
#include <cassert>

void testRedBlackInsertAndPrint() {
	RedBlackTree<std::string, int> rb;

	rb.insert("Emilson", 7);
	rb.insert("Mislayne", 8);
	rb.insert("Miranda", 7);
	rb.insert("Karen", 5);
	rb.insert("Emilly", 6);
	rb.insert("Emanuel", 7);

	std::cout << "Red-Black Tree after insertions:" << std::endl;
	rb.print();
}

void testRedBlackUpdate() {
	RedBlackTree<std::string, int> rb;

	rb.insert("Emilson", 7);
	rb.insert("Mislayne", 8);

	std::cout << "Updating value of 'Emilson' to 10." << std::endl;
	rb.update("Emilson", 10);

	int value = 0;
	assert(rb.find("Emilson", value) && value == 10);

	std::cout << "Updating value of 'Mislayne' to 12." << std::endl;
	rb.update("Mislayne", 12);

	assert(rb.find("Mislayne", value) && value == 12);

	try {
		std::cout << "Attempting to update non-existent key 'Karen'." << std::endl;
		rb.update("Karen", 5);
		assert(false); // Fail the test if no exception is thrown
	} catch (const std::exception& e) {
		std::cout << "Caught exception as expected: " << e.what() << std::endl;
	}

	std::cout << "Red-Black Tree after updates:" << std::endl;
	rb.print();
}

void testRedBlackFind() {
	RedBlackTree<std::string, int> rb;

	rb.insert("Emilson", 7);
	rb.insert("Mislayne", 8);
	rb.insert("Miranda", 7);

	rb.print();

	int value = 0;
	std::string key = "Mislayne";

	if (rb.find(key, value)) {
		std::cout << "Element " << key << " found in the tree with value: " << value << std::endl;
		assert(value == 8);
	} else {
		std::cout << "Element " << key << " not found in the tree." << std::endl;
		assert(false); // Fail the test if the element is not found
	}

	key = "Karen";
	if (!rb.find(key, value)) {
		std::cout << "Element " << key << " not found in the tree as expected." << std::endl;
	} else {
		std::cout << "Unexpectedly found element " << key << " in the tree." << std::endl;
		assert(false); // Fail the test if the element is unexpectedly found
	}
}

// makes a function who tests whether remove node in red-black tree is working
void testRedBlackRemove() {
	RedBlackTree<std::string, int> rb;

	rb.insert("Emilson", 7);
	rb.insert("Mislayne", 8);
	rb.insert("Miranda", 7);
	rb.insert("Karen", 5);
	rb.insert("Emilly", 6);
	rb.insert("Emanuel", 7);

	std::cout << "Red-Black Tree before removals:" << std::endl;
	rb.print();

	std::cout << "Removing 'Karen' from the tree." << std::endl;
	rb.remove("Karen");

	int value = 0;
	assert(!rb.find("Karen", value)); // Ensure 'Karen' is no longer in the tree

	std::cout << "Removing 'Emilson' from the tree." << std::endl;
	rb.remove("Emilson");

	assert(!rb.find("Emilson", value)); // Ensure 'Emilson' is no longer in the tree
	rb.remove("NonExistent");

	std::cout << "Red-Black Tree after removals:" << std::endl;
	rb.print();
}

void testRedBlackClear() {
	RedBlackTree<std::string, int> rb;

	rb.insert("Emilson", 7);
	rb.insert("Mislayne", 8);
	rb.insert("Miranda", 7);
	rb.insert("Karen", 5);
	rb.insert("Emilly", 6);
	rb.insert("Emanuel", 7);

	std::cout << "Red-Black Tree before clearing:" << std::endl;
	rb.print();

	std::cout << "Clearing the tree." << std::endl;
	rb.clear();

	std::cout << "Red-Black Tree after clearing:" << std::endl;
	rb.print();

	int value = 0;
	assert(!rb.find("Emilson", value)); // Ensure the tree is empty
	assert(!rb.find("Mislayne", value));
	assert(!rb.find("Miranda", value));
	assert(!rb.find("Karen", value));
	assert(!rb.find("Emilly", value));
	assert(!rb.find("Emanuel", value));
}

void testRedBlackPrintInOrder() {
	RedBlackTree<std::string, int> rb;

	rb.insert("Emilson", 7);
	rb.insert("Mislayne", 8);
	rb.insert("Miranda", 7);
	rb.insert("Karen", 5);
	rb.insert("Emilly", 6);
	rb.insert("Emanuel", 7);

	std::cout << "Red-Black Tree in-order traversal:" << std::endl;
	std::cout << "Number of comparisons: " << rb.getComparisonsCount() << std::endl;
	rb.printInOrder(std::cout);
}

void testRedBlackOperatorAccess() {
	RedBlackTree<std::string, int> rb;

	rb["Emilson"] = 7;
	rb["Mislayne"] = 8;
	rb["Miranda"] = 7;

	std::cout << "Testing operator[] for access and modification:" << std::endl;

	assert(rb["Emilson"] == 7);
	assert(rb["Mislayne"] == 8);
	assert(rb["Miranda"] == 7);

	std::cout << "Modifying values using operator[]:" << std::endl;
	rb["Emilson"] = 10;
	rb["Mislayne"] = 12;

	assert(rb["Emilson"] == 10);
	assert(rb["Mislayne"] == 12);

	std::cout << "Accessing a non-existent key to insert it:" << std::endl;
	rb["Karen"] = 5;
	assert(rb["Karen"] == 5);

	std::cout << "Red-Black Tree after operator[] tests:" << std::endl;
	rb.print();

	rb.printInOrder(std::cout);
}

void testRedBlackConstOperatorAccess() {
	const RedBlackTree<std::string, int> rb = []() {
		RedBlackTree<std::string, int> temp;
		temp.insert("Emilson", 7);
		temp.insert("Mislayne", 8);
		temp.insert("Miranda", 7);
		return temp;
	}();

	std::cout << "Testing const operator[] for access:" << std::endl;

	assert(rb["Emilson"] == 7);
	assert(rb["Mislayne"] == 8);
	assert(rb["Miranda"] == 7);

	std::cout << "Const operator[] tests passed successfully!" << std::endl;
}

void testRedBlackRotationsCount() {
	RedBlackTree<std::string, int> temp;

	temp.insert("Emilson", 7);
	temp.insert("Mislayne", 8);
	temp.insert("Miranda", 7);

	std::cout << "Número de rotações: " << temp.getRotationsCount() << std::endl;
}

int main() {
	testRedBlackInsertAndPrint();
	testRedBlackFind();
	testRedBlackUpdate();
	testRedBlackRemove();
	testRedBlackClear();
	testRedBlackPrintInOrder();
	testRedBlackOperatorAccess();
	testRedBlackConstOperatorAccess();
	testRedBlackRotationsCount();

	std::cout << "All Red-Black Tree tests completed successfully!" << std::endl;
	return 0;
}
#include "Trees/AVL/AVLTree.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

void printTestHeader(const std::string& title) {
    std::cout << "\n===================================================\n";
    std::cout << "TEST: " << title << "\n";
    std::cout << "===================================================\n";
}

template <typename Key, typename Value>
void printTreeInOrder(const AVLTree<Key, Value>& avl, const std::string& message) {
    std::cout << "\n--- " << message << " ---\n";
    avl.printInOrder(std::cout);
    std::cout << "-------------------------------------------\n";
}

template <typename Key, typename Value>
void printTreeStructure(const AVLTree<Key, Value>& avl, const std::string& message) {
    std::cout << "\n--- " << message << " (Structure) ---\n";
    avl.print();
    std::cout << "-------------------------------------------\n";
}

void testBasicInsertionsAndBalance() {
    printTestHeader("Basic Insertions & Self-Balancing (Visual Inspection)");
    AVLTree<std::string, int> avl;

    std::cout << "Inserting elements: 'Banana', 'Apple', 'Cherry', 'Date', 'Fig', 'Grape', 'Elderberry'\n";
    avl.insert("Banana", 10);
    avl.insert("Apple", 5);
    avl.insert("Cherry", 15);
    avl.insert("Date", 20); 
    avl.insert("Fig", 25);
    avl.insert("Grape", 30);
    avl.insert("Elderberry", 18);

    printTreeInOrder(avl, "Tree after multiple insertions (in-order)");
    printTreeStructure(avl, "Tree structure after insertions");

    std::cout << "Total comparisons after insertions: " << avl.getComparisonsCount() << std::endl;
    std::cout << "Total rotations after insertions: " << avl.getRotationsCount() << std::endl;

    int val;
    assert(avl.find("Apple", val) && val == 5);
    assert(avl.find("Cherry", val) && val == 15);
    std::cout << "Assertions for key values passed.\n";

    std::cout << "Attempting to insert a duplicate key 'Apple' (should throw exception).\n";
    try {
        avl.insert("Apple", 6);
        assert(false && "KeyAlreadyExistsException was not thrown for duplicate insert.");
    } catch (const KeyAlreadyExistsException& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

void testFindOperations() {
    printTestHeader("Find Operations");
    AVLTree<std::string, int> avl;
    avl.insert("Alpha", 1);
    avl.insert("Beta", 2);
    avl.insert("Gamma", 3);

    int outValue = 0;
    std::string existingKey = "Beta";
    std::string nonExistingKey = "Delta";

    std::cout << "Searching for existing key: '" << existingKey << "'\n";
    bool found = avl.find(existingKey, outValue);
    assert(found && outValue == 2);
    std::cout << "Found '" << existingKey << "' with value " << outValue << ". Comparisons: " << avl.getComparisonsCount() << std::endl;

    std::cout << "Searching for non-existing key: '" << nonExistingKey << "'\n";
    found = avl.find(nonExistingKey, outValue);
    assert(!found);
    std::cout << "Did not find '" << nonExistingKey << "'. Comparisons: " << avl.getComparisonsCount() << std::endl;
    std::cout << "Find operations tests passed.\n";
}

void testUpdateOperations() {
    printTestHeader("Update Operations");
    AVLTree<std::string, int> avl;
    avl.insert("Quick", 100);
    avl.insert("Brown", 200);
    avl.insert("Fox", 300);

    printTreeInOrder(avl, "Tree before update");

    std::cout << "Updating 'Brown' from 200 to 250.\n";
    avl.update("Brown", 250);
    int val = 0;
    assert(avl.find("Brown", val) && val == 250);
    printTreeInOrder(avl, "Tree after updating 'Brown'");
    std::cout << "Update successful. Comparisons: " << avl.getComparisonsCount() << std::endl;

    std::string nonExistingKey = "Lazy";
    std::cout << "Attempting to update non-existing key: '" << nonExistingKey << "' (should throw exception).\n";
    try {
        avl.update(nonExistingKey, 999);
        assert(false && "KeyNotFoundException was not thrown for non-existent update.");
    } catch (const KeyNotFoundException& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "Update operations tests passed.\n";
}

void testOperatorAccessAndUpsert() {
    printTestHeader("Operator[] Access (Upsert Functionality)");
    AVLTree<std::string, int> avl;

    std::cout << "Using operator[] to insert new keys:\n";
    avl["Dino"] = 10;
    avl["Elephant"] = 20;
    avl["Falcon"] = 30;
    printTreeInOrder(avl, "Tree after new insertions with operator[]");
    printTreeStructure(avl, "Tree structure after operator[] insertions");

    assert(avl["Dino"] == 10);
    assert(avl["Elephant"] == 20);
    assert(avl["Falcon"] == 30);
    std::cout << "New key insertions via operator[] verified.\n";

    std::cout << "Using operator[] to update existing keys:\n";
    avl["Dino"] = 15;
    avl["Falcon"] = 35;
    printTreeInOrder(avl, "Tree after updates with operator[]");
    printTreeStructure(avl, "Tree structure after operator[] updates");

    assert(avl["Dino"] == 15);
    assert(avl["Falcon"] == 35);
    std::cout << "Existing key updates via operator[] verified.\n";
    std::cout << "Total comparisons after operator[] operations: " << avl.getComparisonsCount() << std::endl;
    std::cout << "Total rotations after operator[] operations: " << avl.getRotationsCount() << std::endl;

    std::cout << "Testing const operator[] for read-only access (no modification):\n";
    const AVLTree<std::string, int>& constAvl = avl;
    assert(constAvl["Elephant"] == 20);
    std::cout << "Const operator[] access verified.\n";

    std::cout << "Operator[] (Upsert) tests passed.\n";
}

void testRemoveOperations() {
    printTestHeader("Remove Operations");
    AVLTree<int, std::string> avl;

    std::vector<int> keys_to_insert = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    for (int key : keys_to_insert) {
        avl.insert(key, "Value-" + std::to_string(key));
    }
    printTreeInOrder(avl, "Initial tree for removals (in-order)");
    printTreeStructure(avl, "Initial tree structure for removals");
    std::cout << "Initial rotations: " << avl.getRotationsCount() << std::endl;

    std::cout << "Removing a leaf node (10).\n";
    avl.remove(10);
    std::string val_str;
    assert(!avl.find(10, val_str));
    printTreeInOrder(avl, "After removing 10");
    printTreeStructure(avl, "Structure after removing 10");

    std::cout << "Removing a node with one child (20).\n";
    avl.remove(20);
    assert(!avl.find(20, val_str));
    printTreeInOrder(avl, "After removing 20");
    printTreeStructure(avl, "Structure after removing 20");

    std::cout << "Removing a node with two children (70).\n";
    avl.remove(70);
    assert(!avl.find(70, val_str));
    printTreeInOrder(avl, "After removing 70");
    printTreeStructure(avl, "Structure after removing 70");

    std::cout << "Removing the root (50).\n";
    avl.remove(50);
    assert(!avl.find(50, val_str));
    printTreeInOrder(avl, "After removing 50 (new root)");
    printTreeStructure(avl, "Structure after removing 50");

    std::cout << "Attempting to remove a non-existent key (99).\n";
    size_t initial_rotations = avl.getRotationsCount();
    avl.remove(99);
    assert(avl.getRotationsCount() == initial_rotations);
    std::cout << "Removing non-existent key had no effect as expected.\n";

    std::cout << "Total rotations during remove operations: " << avl.getRotationsCount() << std::endl;
    std::cout << "Remove operations tests passed.\n";
}

void testClearFunctionality() {
    printTestHeader("Clear Functionality");
    AVLTree<std::string, double> avl;

    avl.insert("One", 1.1);
    avl.insert("Two", 2.2);
    avl.insert("Three", 3.3);

    printTreeInOrder(avl, "Tree before clearing");
    assert(avl.getComparisonsCount() > 0 || avl.getRotationsCount() > 0);

    std::cout << "Clearing the tree...\n";
    avl.clear();

    double d_val;
    assert(!avl.find("One", d_val));
    assert(!avl.find("Two", d_val));
    assert(!avl.find("Three", d_val));

    std::cout << "Tree after clearing (should be empty):\n";
    avl.printInOrder(std::cout);
    avl.print();

    std::cout << "Attempting to insert after clear.\n";
    avl.insert("NewItem", 99.9);
    assert(avl.find("NewItem", d_val) && d_val == 99.9);
    printTreeInOrder(avl, "Tree after re-inserting into cleared tree");

    std::cout << "Clear functionality test passed.\n";
}

void testComprehensiveScenario() {
    printTestHeader("Comprehensive Mixed Operations Scenario");
    AVLTree<char, int> avl;

    std::cout << "Phase 1: Initial insertions (some causing rotations).\n";
    avl.insert('M', 13);
    avl.insert('F', 6);
    avl.insert('S', 19);
    avl.insert('B', 2);
    avl.insert('H', 8);
    avl.insert('P', 16);
    avl.insert('U', 21);
    avl.insert('D', 4);
    avl.insert('L', 12);
    avl.insert('T', 20);
    avl.insert('Z', 26);
    printTreeInOrder(avl, "After initial insertions");
    printTreeStructure(avl, "Structure after initial insertions");
    std::cout << "Current comparisons: " << avl.getComparisonsCount() << ", rotations: " << avl.getRotationsCount() << std::endl;

    std::cout << "\nPhase 2: Updates and new inserts via operator[].\n";
    avl['D'] = 40;
    avl['A'] = 1;
    avl['C'] = 3;
    avl['Q'] = 17;
    printTreeInOrder(avl, "After updates and operator[] inserts");
    printTreeStructure(avl, "Structure after updates and operator[] inserts");
    assert(avl['D'] == 40);
    assert(avl['A'] == 1);
    std::cout << "Current comparisons: " << avl.getComparisonsCount() << ", rotations: " << avl.getRotationsCount() << std::endl;

    std::cout << "\nPhase 3: Removals (testing various cases).\n";
    std::cout << "Removing 'H' (leaf).\n";
    avl.remove('H');
    std::cout << "Removing 'U' (node with one child).\n";
    avl.remove('U');
    std::cout << "Removing 'F' (node with two children).\n";
    avl.remove('F');
    std::cout << "Removing 'M' (original root, likely causes complex rebalancing).\n";
    avl.remove('M');

    printTreeInOrder(avl, "After several removals");
    printTreeStructure(avl, "Structure after several removals");

    int int_val;
    assert(!avl.find('H', int_val));
    assert(!avl.find('U', int_val));
    assert(!avl.find('F', int_val));
    assert(!avl.find('M', int_val));

    std::cout << "Current comparisons: " << avl.getComparisonsCount() << ", rotations: " << avl.getRotationsCount() << std::endl;

    std::cout << "\nPhase 4: Final checks.\n";
    int outVal;
    assert(avl.find('P', outVal) && outVal == 16);
    assert(avl.find('A', outVal) && outVal == 1);
    std::cout << "Final checks passed. Comparisons: " << avl.getComparisonsCount() << std::endl;

    std::cout << "Comprehensive scenario test passed.\n";
}

int main() {
    try {
        testBasicInsertionsAndBalance();
        testFindOperations();
        testUpdateOperations();
        testOperatorAccessAndUpsert();
        testRemoveOperations();
        testClearFunctionality();
        testComprehensiveScenario();

        std::cout << "\n\nAll AVL Tree tests completed successfully! The implementation rocks!\n";
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

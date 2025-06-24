#include "Trees/AVL/AVLTree.hpp"

int main() {
    AVLTree<std::string, int> avl;

    avl["Érica"] = 0;
    avl["Bruna"] = 1;
    avl["Paulo"] = 2;
    avl["Mislayne"] = 2;

    avl.printInOrder(std::cout);

    return 0;
}
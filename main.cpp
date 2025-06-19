#include "AVLTree.hpp"

int main() {
	AVLTree<std::string, int> avl;
	avl.insert("Emilson", 7);
	avl.insert("Mislayne", 8);
	avl.insert("Miranda", 7);
	avl.insert("Karen", 5);
	avl.insert("Emilly", 6);
	avl.insert("Emanuel", 7);
	avl.update("Willian", 7);
	avl.update("Calebe", 6);
	avl.remove("Iago");
	avl.print();

	int out = 0;
	std::string name = "Willian";
	if (avl.find(name, out)) {
		std::cout << "elemento " << name << " está na lista? " << std::boolalpha << true << std::endl;
		std::cout << "valor: " << out << std::endl;
	} else {
		std::cout << "elemento " << name << " não está na lista" << std::endl;
	}


	return 0;
}
#include "Trees/AVL/AVLTree.hpp"
#include <iostream>

using namespace std;

int main() {
    AVLTree<int, float> avl;

    avl[1] = 0.9;

    cout << "Árvore após primeira inserção:\n";
    avl.printInOrder(cout);

    avl.clear();
    cout << "Árvore após clear:\n"; // Não deve imprimir nada
    
    cout << "Inserindo valores repetidos em 14...\n";
    avl[14] = 0.146;
    avl[30] = 0.908;
    avl[14] = 0.232;
    avl[14] = 0.991;

    cout << "Número de rotações até o presente momento (deve ser 0): " << avl.getRotationsCount() << endl;

    cout << "A estrutura só deve ter 14 e 30.\n";
    avl.print();
    avl.printInOrder(cout); 

    avl.insert(29, 0.016); // provoca rotação dupla (+2 rotações)
    avl.insert(4, 0.873);
    avl.insert(7, 0.404); // provoca rotação dupla (+2 rotações)
    avl.insert(2, 0.995); // provoca rotação simples (+1 rotação)

    cout << "Conferindo elementos após sucessivas inserções\n";
    avl.print();
    cout << "Número de rotações até o presente momento (deve ser 5): " << avl.getRotationsCount() << endl;

    avl[17] = 0.893;
    avl[23] = 0.910; // provoca rotação simples (+1 rotação)
    avl[11] = 0.082; // provoca rotação simples (+1 rotação)

    cout << "Conferindo elementos após sucessivas inserções\n";
    avl.print();
    avl.printInOrder(cout);

    try {
        avl.insert(23, 0.314);
        avl.insert(13, 0.777);
        avl.insert(7, 0.745);
        avl.insert(25, 0.897);
        avl.insert(28, 0.909);
    } catch(const KeyAlreadyExistsException& e) {
        cout << e.what() << endl;
    }

    cout << "Conferindo elementos após sucessivas inserções (a estrutura não deve ter sido alterada)\n";
    avl.print();

    avl.printInOrder(cout);
    cout << "Número de rotações até o presente momento (deve ser 5): " << avl.getRotationsCount() << endl;

    return 0;
}

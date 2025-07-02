#include "Trees/AVL/AVLTree.hpp"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    AVLTree<int, float> avl;

    avl[1] = 0.9;

    cout << "Árvore após primeira inserção:\n";
    avl.printInOrder(cout);

    avl.clear();
    cout << "Limpando a árvore...\nTentando printar depois do clear\n";
    cout << "Árvore após clear:\n"; // Não deve imprimir nada
    cout << "Número de rotações: " << avl.getRotationsCount() << endl
         << "Número de comparações: " << avl.getComparisonsCount() << endl;
    
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
    cout << "Número de rotações até o presente momento (deve ser 7): " << avl.getRotationsCount() << endl;

    float searched = 0;
    vector<int> values = {8,27,28};

    for (int val : values) {
        if (avl.find(val, searched)) {
            cout << "Erro: Valor inexistente retornando true\n";
            return 1;
        }
    }

    avl.find(14, searched);
    assert(searched == 0.991f);
    
    avl.find(29, searched);
    assert(searched == 0.016f);

    avl[30] = 0.3;

    cout << "Após o upsert, a estrutura da árvore deve continuar a mesma\n";
    avl.print();

    values = {19,26};

    for (int val : values) {
        if (avl.find(val, searched)) {
            cout << "Erro: Valor inexistente retornando true\n";
            return 1;
        }
    }

    try {
        avl.insert(1, 0.341); // provoca uma rotação à direita (+1 rotação)
        avl.insert(1, 0.341);
    } catch (const KeyAlreadyExistsException& e) {
        cout << e.what() << endl;
    }

    cout << "Após a inserção, o número 1 deve estar inserido com o valor 0.341\n";
    avl.print();
    cout << "Número de rotações até o presente momento (deve ser 8): " << avl.getRotationsCount() << endl;    

    values = {24,26};

    for (int val : values) {
        if (avl.find(val, searched)) {
            cout << "Erro: Valor inexistente retornando true\n";
            return 1;
        }
    }

    try {
        avl.update(14, 0.321);
        avl.update(8, 0); // deve lançar exceção 
    } catch (const KeyNotFoundException& e) {
        cout << "KeyNotFoundException lançado, como esperado\n";
    }

    cout << "14 deve estar atualizado com 0.321:\n";
    avl.printInOrder(cout);

    cout << "Número total de comparações: " << avl.getComparisonsCount() << endl;

    return 0;
}

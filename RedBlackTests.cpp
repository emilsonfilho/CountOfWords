#include "Trees/RedBlack/RedBlackTree.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

int main() {
    RedBlackTree<float, string> rb;

    rb.insert(6.92f, "Abacaxi");
    rb.insert(10.25f, "Goiaba");

    rb[1.55f] = "Pitanga";
    rb[6.92f] = "Maracujá";
    rb[6.45f] = "Banana";
    rb[8.88f] = "Maracujá";

    cout << "Chave 6.92 deve ter valor Maracujá:\n";
    rb.print();
    rb.printInOrder(cout);

    cout << "Número de rotações: " << rb.getRotationsCount() << endl
         << "Número de comparações: " << rb.getComparisonsCount() << endl;

    rb.clear();

    cout << "Limpando a árvore...\nTentando printar depois do clear\n";
    cout << "Número de rotações: " << rb.getRotationsCount() << endl
         << "Número de comparações: " << rb.getComparisonsCount() << endl;

    try {
        rb.update(1.55f, "Acerola");
    } catch (const KeyNotFoundException& e) {
        cout << "Chave não encontrada, como esperado.\n";
    }

    rb.insert(3.84f, "Graviola");

    rb.printInOrder(cout);

    rb[1.55f] = "Amora";

    rb[7.16f] = "Laranja";
    rb[9.4f] = "Morango";
    rb[2.55f] = "Amora";
    rb[6.41f] = "Abacaxi";
    rb[4.42f] = "Amora";
    rb[10.67f] = "Figo";

    string result = "";
    vector<float> v = {7.16f, 9.4f, 2.55f, 6.41f, 4.42f, 10.67f};
    vector<string> expected = {"Laranja", "Morango", "Amora", "Abacaxi", "Amora", "Figo"};

    for (int i = 0; i < v.size(); i++) {
        rb.find(v[i], result);
        assert(result == expected[i]);
    }

    rb.print();

    rb.clear();

    rb.insert(5.08f, "Morango");

    result = "";
    v = {7.16f, 9.4f, 2.55f, 6.41f, 4.42f, 10.67f};

    for (int i = 0; i < v.size(); i++) {
        if (rb.find(v[i], result)) {
            cout << "Erro: resultado inexistente retornando true\n"; // Essa mensagem não deve ser printada
            return 1;
        }
    }

    rb.clear();
    cout << "Tentando printar árvore limpada:\n";
    rb.print(); // Não deve printar nada

    rb[3.6f] = "Melancia";
    rb.remove(3.6f);
    rb.print();
    rb.remove(0); // Não deve lanar exceões

    return 0;
}

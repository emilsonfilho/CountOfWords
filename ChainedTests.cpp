#include "HashTables/Chained/ChainedHashTable.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <iomanip>

using namespace std;

int main() {
    ChainedHashTable<char, char> tb;

    tb.insert('K', 'M');
    tb.print();
    tb.insert('Q', 'Z');

    cout << tb.getTableSize() << endl;

    tb.printInOrder(cout);

    tb.remove('N');
    tb.remove('Q');

    cout << "Fator de carga (deve ser 1/11 = 0.9090...): " << tb.getLoadFactor() << endl;

    tb.insert('N', 'Q');
    tb.insert('R', 'V');
    tb.insert('J', 'H');
    tb.insert('Y', 'R'); // deve colidir com N
    tb.insert('A', 'B');

    tb.print();

    cout << "Número de colisões (deve ser 1): " << tb.getCollissionsCount() << endl;

    cout << "Limpando tabela...\n";
    tb.clear();

    tb.print();

    char searched = ' ';
    tb.find('N', searched);

    assert(searched == ' ');

    try {
        tb.update('N', 'O');
    } catch (const KeyNotFoundException& e) {
        cout << "Chave após clear não encontrada, como esperado.\n";
    }

    tb.remove('C');

    cout << "Comparisons count após clear (deve ser 0): " << tb.getComparisonsCount() << endl;


    try {
        tb.insert('C', 'A');
        tb.insert('D', 'W');
        tb.insert('H', 'F');
        tb.insert('V', 'Q');
        tb.insert('C', 'A'); 
    } catch (const KeyAlreadyExistsException& e) {
        cout << "Última operação falhou apontando chave já existente como esperado\nPrinte a estrutura pra se certificar de que os passos anteriores foram concluídos\n";
    }

    tb.print();
    cout << "Número de comparações: " << tb.getComparisonsCount() << endl;

    tb['N'] = 'I'; // colide com C
    tb['U'] = 'D';

    cout << "Fator de carga (deve ser 6/11 = 0.5454...): " << tb.getLoadFactor() << endl;

    tb.insert('Y', 'L'); // colide com C e N
    tb.insert('O', 'M'); // colide com D
    tb.insert('Z', 'W'); // colide com D e O

    cout << "Número de colisões (deve ser 4): " << tb.getCollissionsCount() << endl;

    try {
        tb.update('H', 'D');
        tb.update('A', 'Y');
    } catch (const KeyNotFoundException& e) {
        cout << "Última operação lançou exceção como esperado. H deve ter sido atualizado\n";
    }

    tb.printInOrder(cout);

    tb.remove('Y');
    tb.remove('C');

    cout << "Estrutura após remoção\n";
    tb.print();

    cout << "Fator de carga (deve ser 7/11 = 0.6363...): " << tb.getLoadFactor() << endl;

    cout << "Número de colisões: " << tb.getCollissionsCount() << endl
         << "Número de comparações: " << tb.getComparisonsCount() << endl;

    tb.clear();

    return 0;
}

#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <iomanip>

using namespace std;

int main() {
    OpenAddressingHashTable<char, int> tb;
    
    tb.remove('.');
    cout << "Número de comparações (deve ser 0): " << tb.getComparisonsCount() << endl;
    try {
        tb.update('?', '?');
    } catch (const KeyNotFoundException& e) {
        cout << "Valor não encontrado como o esperado.\n";
    }

    int value = 0;
    assert(!tb.find('!', value) && value == 0);

    tb.printInOrder(cout);

    cout << "Número de comparações: " << tb.getComparisonsCount() << endl
         << "Número de colisões (esperado 0): " << tb.getCollisionsCount() << endl;

    tb.insert('?', '?');
    tb.insert('.', '.');
    tb.insert(';', ';'); 
    tb.insert('+', '+'); // colisão com ;
    tb.insert(',', ','); // colisão com o mapeamento de +

    cout << "Tamanho da tabela: " << tb.getTableSize() << endl
         << "Número de comparações: " << tb.getComparisonsCount() << endl
         << "Número de colisões (esperado 2): " << tb.getCollisionsCount() << endl;

    tb.printInOrder(cout);
    tb.print();

    tb['-'] = '-';
    tb['{'] = '{';
    tb['+'] = 100; // não deve alterar o número de colisoes

    cout << "Tamanho da tabela: " << tb.getTableSize() << endl
         << "Número de comparações: " << tb.getComparisonsCount() << endl
         << "Número de colisões (esperado 2): " << tb.getCollisionsCount() << endl;

    tb.printInOrder(cout);
    tb.print();

    cout << "Removendo valores...\n";
    tb.remove('-');
    tb.remove(';');
    tb.remove('.');
    tb.remove('a');

    tb.print();

    cout << "Testando inserir em posição deletada\n";
    tb.insert(75, 11); // deve inseir em no slot de ; (11), seguindo 11+16*4 = 'K'

    tb.print();

    cout << "Tamanho da tabela: " << tb.getTableSize() << endl
         << "Número de comparações: " << tb.getComparisonsCount() << endl
         << "Número de colisões: " << tb.getCollisionsCount() << endl;    

    return 0;
}

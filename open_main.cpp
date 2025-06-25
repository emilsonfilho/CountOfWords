#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <iostream>

int main() {
    OpenAddressingHashTable<std::string, int> oaht;

    oaht.insert("apple", 12);
    oaht.insert("banana", 7);
    oaht.insert("cherry", 42);
    oaht.insert("dragonfruit", 5);
    oaht.insert("elderberry", 23);
    oaht.insert("fig", 9);
    oaht.insert("grape", 31);
    oaht.insert("honeydew", 16);
    
    oaht.insert("kiwi", 3);
    oaht.insert("lemon", 18);
    oaht.insert("mango", 14);
    oaht.insert("nectarine", 27);
    oaht.insert("orange", 11);
    oaht.insert("papaya", 6);
    oaht.insert("quince", 30);

    int sla = 0;
    if (oaht.find("orange", sla)) {
        std::cout << "orange foi encontrado com valor " << sla << std::endl;
    } else std::runtime_error("ORANGE NAO FOI ENCONtRADO\n");

    if (!oaht.find("mamao", sla)) {
        std::cout << "nao foi possivel encontrar mamao como o esperdo\n";
    }

    oaht.printInOrder(std::cout);

    return 0;
}
#include "HashTables/Chained/ChainedHashTable.hpp"

int main() {
    ChainedHashTable<std::string, int> cht;
    
    cht.insert("Érica", 7);
    cht.insert("Paulo", 7);
    cht.insert("Paula", 7);
    cht.insert("Lucas", 7);
    cht.insert("Bruna", 7);
    cht["Mislayne"] = 9;
    cht.insert("Calebe", 6);
    cht.insert("Isadora", 7);
    cht.insert("Karen", 5);
    cht.insert("Emilly", 6);
    cht.insert("Emanuel", 7);

    cht.update("Emilly", 9);

    // int val = 0;
    // std::cout << "Miranda was found? " << std::boolalpha << cht.find("Miranda", val) << std::endl;

    cht["Miranda"] = 7;
    cht["Emilson"] = 0;
    cht["Atílio"] = 0;

    cht.printInOrder(std::cout);
    std::cout << "Número de colisões: " << cht.getCollissionsCount() << std::endl;
    std::cout << "Tamanho da tabela: " << cht.getTableSize() << '\n';

    return 0;
}
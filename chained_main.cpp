#include "HashTables/ChainedHashTable.hpp"

int main() {
    ChainedHashTable<std::string, int> cht;
    
    cht.insert("Emilson", 7);
    cht.insert("Calebe", 6);
    cht.insert("Isadora", 7);
    cht.insert("Mislayne", 7);
    cht.insert("Karen", 5);
    cht.insert("Emilly", 6);
    cht.insert("Emanuel", 7);

    cht.update("Emilson", 10);
    cht.update("Emilly", 9);

    int val = 0;
    std::cout << "Miranda was found? " << std::boolalpha << cht.find("Miranda", val) << std::endl;

    cht["Miranda"] = 7;
    cht["Emilson"] = 0;
    cht["Atílio"] = 0;

    cht.printInOrder(std::cout);

    return 0;
}
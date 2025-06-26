#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <iostream>

int main() {
    OpenAddressingHashTable<std::string, int> oaht;

    oaht["banana"] = 7;
    oaht["cherry"] = 42;
    oaht["dragonfruit"] = 5;
    oaht["elderberry"] = 23;
    oaht["fig"] = 9;
    oaht["grape"] = 31;
    oaht["honeydew"] = 16;
    oaht["kiwi"] = 3;
    oaht["lemon"] = 18;
    oaht["mango"] = 14;
    oaht["nectarine"] = 27;
    oaht["orange"] = 11;
    oaht["papaya"] = 6;
    oaht["quince"] = 30;


    oaht["apple"] = 12;

    // oaht.update("kiwi", 4);
    // oaht.remove("mango");
    oaht.clear();

    std::cout << "numero de comparacoes " << oaht.getComparisonsCount() << std::endl;

    oaht.printInOrder(std::cout);

    return 0;
}
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <iomanip>

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << std::string((70 - title.length()) / 2, ' ') << title << "\n";
    std::cout << std::string(70, '=') << std::endl;
}

void testBasicProbingAndOperations() {
    printHeader("Teste Basico: Inventario da Loja de Pecoes");
    
    OpenAddressingHashTable<std::string, int> potionShop(8);

    std::cout << "\n--- Fase 1: Estocando o Inventario (Insercoes) ---\n";
    potionShop.insert("Healing Potion", 50);
    potionShop.insert("Mana Potion", 30);
    potionShop.insert("Invisibility Potion", 5);
    potionShop.insert("Strength Potion", 15);
    
    potionShop["Stamina Potion"] = 20;
    potionShop["Healing Potion"] = 55;

    std::cout << "Inventario atual (em ordem alfabetica):" << std::endl;
    potionShop.printInOrder(std::cout);

    std::cout << "\n>> Status da Tabela:" << std::endl;
    std::cout << "Numero de Colisoes: " << potionShop.getCollisionsCount() << std::endl;
    std::cout << "Numero de Comparacoes: " << potionShop.getComparisonsCount() << std::endl;

    std::cout << "\n--- Fase 2: Verificando o Estoque (Find & Update) ---\n";
    int quantity;
    assert(potionShop.find("Healing Potion", quantity) && quantity == 55);
    assert(potionShop["Strength Potion"] == 15);
    
    std::cout << "Atualizando 'Mana Potion' para 35 unidades.\n";
    potionShop.update("Mana Potion", 35);
    assert(potionShop["Mana Potion"] == 35);
    
    std::cout << "Operacoes basicas validadas com sucesso." << std::endl;
}

void testRehashingAndExceptions() {
    printHeader("Teste de Rehash e Excecoes");
    
    OpenAddressingHashTable<int, std::string> testTable(8, 0.5f);
    
    std::cout << "\n--- Fase 1: Testando Rehash e Limpeza de Slots DELETED ---\n";
    testTable[1] = "Um";
    testTable[9] = "Nove";
    testTable[2] = "Dois";
    testTable.remove(9);

    std::cout << "Inserindo elementos para forcar o rehash...\n";
    testTable[3] = "Tres";
    testTable[4] = "Quatro";

    std::cout << "Tamanho da tabela apos rehash: " << testTable.getTableSize() << std::endl;
    assert(testTable.getTableSize() > 8);
    std::cout << "Rehash ocorreu como esperado. Os slots DELETED foram purgados.\n";
    
    std::string value;
    assert(testTable.find(1, value) && value == "Um");
    assert(!testTable.find(9, value));

    std::cout << "\n--- Fase 2: Testando Excecoes ---\n";
    try {
        std::cout << "Tentando inserir chave duplicada (2)...\n";
        testTable.insert(2, "Dois de novo");
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
    }
    
    const auto& constRefTable = testTable;
    try {
        std::cout << "Tentando acessar chave inexistente (99) em tabela const...\n";
        value = constRefTable[99];
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
    }
}

void testNonBase2TableSize() {
    printHeader("Teste sobre o Preâmbulo de Cormen");

    OpenAddressingHashTable<int, char> testTable(7, 1.0f);

    assert(testTable.getTableSize() == 8);

    std::cout << "TableSize is a power of 2 as expected\n";

    for (int i = 1; i <= 100; i++)
        testTable.insert(i, 'a');

    testTable.printInOrder(std::cout);

    std::cout << "Table size: " << testTable.getTableSize() << '\n';
    
    assert(testTable.getTableSize() == 128);
}

int main() {
    testBasicProbingAndOperations();
    testRehashingAndExceptions();
    testNonBase2TableSize();
    
    std::cout << "\n" << std::string(70, '*') << "\n";
    std::cout << std::string(5, ' ') << "TODOS OS TESTES DE ENDERECAMENTO ABERTO FORAM CONCLUIDOS!" << std::string(5, ' ') << "\n";
    std::cout << std::string(70, '*') << std::endl;

    return 0;
}

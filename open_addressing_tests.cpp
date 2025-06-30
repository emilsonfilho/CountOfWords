#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <iomanip>

// Função auxiliar para organizar a saída dos testes
void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << std::string((70 - title.length()) / 2, ' ') << title << "\n";
    std::cout << std::string(70, '=') << std::endl;
}

/**
 * @brief Testa as operações básicas e a sondagem quadrática.
 *
 * Este teste demonstra:
 * 1.  Criação da tabela e inserção de itens.
 * 2.  Ocorrência de colisões e como a sondagem quadrática as resolve.
 * 3.  Busca, atualização e uso do `operator[]` para acesso e modificação.
 */
void testBasicProbingAndOperations() {
    printHeader("Teste Basico: Inventario da Loja de Pecoes");
    
    // Tamanho inicial pequeno para observar colisões mais facilmente.
    OpenAddressingHashTable<std::string, int> potionShop(8);

    // --- Fase 1: Estocando a loja (Inserções) ---
    std::cout << "\n--- Fase 1: Estocando o Inventario (Insercoes) ---\n";
    potionShop.insert("Healing Potion", 50);
    potionShop.insert("Mana Potion", 30);
    potionShop.insert("Invisibility Potion", 5);
    potionShop.insert("Strength Potion", 15);
    
    // Usando operator[] para adicionar e modificar
    potionShop["Stamina Potion"] = 20; // Adiciona
    potionShop["Healing Potion"] = 55;  // Atualiza um item existente

    std::cout << "Inventario atual (em ordem alfabetica):" << std::endl;
    potionShop.printInOrder(std::cout);

    std::cout << "\n>> Status da Tabela:" << std::endl;
    std::cout << "Numero de Colisoes: " << potionShop.getCollisionsCount() << std::endl; //
    std::cout << "Numero de Comparacoes: " << potionShop.getComparisonsCount() << std::endl; //

    // --- Fase 2: Verificação do estoque ---
    std::cout << "\n--- Fase 2: Verificando o Estoque (Find & Update) ---\n";
    int quantity;
    assert(potionShop.find("Healing Potion", quantity) && quantity == 55);
    assert(potionShop["Strength Potion"] == 15);
    
    std::cout << "Atualizando 'Mana Potion' para 35 unidades.\n";
    potionShop.update("Mana Potion", 35);
    assert(potionShop["Mana Potion"] == 35);
    
    std::cout << "Operacoes basicas validadas com sucesso." << std::endl;
}

/**
 * @brief Testa o rehash e o tratamento de exceções.
 *
 * Demonstra:
 * 1.  O rehash automático quando o fator de carga é excedido.
 * 2.  Que o rehash "limpa" os slots DELETED, pois apenas elementos ACTIVE são reinseridos.
 * 3.  O tratamento correto de exceções para chaves duplicadas e não encontradas.
 */
void testRehashingAndExceptions() {
    printHeader("Teste de Rehash e Excecoes");
    
    // Fator de carga de 0.5. Com tamanho 8, o 5º elemento deve causar rehash.
    OpenAddressingHashTable<int, std::string> testTable(8, 0.5f);
    
    std::cout << "\n--- Fase 1: Testando Rehash e Limpeza de Slots DELETED ---\n";
    testTable[1] = "Um";
    testTable[9] = "Nove"; // Colide com 1
    testTable[2] = "Dois";
    testTable.remove(9); // O slot de "Nove" agora é DELETED

    std::cout << "Inserindo elementos para forcar o rehash...\n";
    testTable[3] = "Tres";
    testTable[4] = "Quatro"; // Deve disparar o rehash aqui (5º elemento ativo > 8 * 0.5)

    std::cout << "Tamanho da tabela apos rehash: " << testTable.getTableSize() << std::endl;
    assert(testTable.getTableSize() > 8);
    std::cout << "Rehash ocorreu como esperado. Os slots DELETED foram purgados.\n";
    
    // Verifica se os elementos ativos foram mantidos
    std::string value;
    assert(testTable.find(1, value) && value == "Um");
    assert(!testTable.find(9, value)); // "Nove" foi removido e purgado no rehash.

    // --- Fase 2: Tratamento de Exceções ---
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
        value = constRefTable[99]; // Deve lançar KeyNotFoundException
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
    
    // 8 -> 16 -> 32 -> 64 -> 128
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
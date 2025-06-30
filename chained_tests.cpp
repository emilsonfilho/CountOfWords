#include "HashTables/Chained/ChainedHashTable.hpp"
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
 * @brief Testa a funcionalidade basica: insercao, busca, atualizacao e remocao.
 *
 * Este teste demonstra:
 * 1.  Criação de uma tabela com tamanho inicial pequeno para forçar colisões.
 * 2.  Inserção de múltiplos elementos e verificação das contagens de colisão e comparação.
 * 3.  Uso do `operator[]` para inserir e modificar elementos.
 * 4.  Uso dos métodos `update()` e `remove()`.
 * 5.  Verificação da integridade dos dados após cada operação.
 */
void testBasicFunctionality() {
    printHeader("Teste de Funcionalidade Basica: Frota Estelar");
    
    ChainedHashTable<std::string, std::string> fleet(5);

    std::cout << "\n--- Fase 1: Comissionando a Frota (Insercoes) ---\n";
    fleet.insert("Kirk", "USS Enterprise");
    fleet.insert("Picard", "USS Enterprise-D");
    fleet.insert("Sisko", "Deep Space 9");
    fleet.insert("Janeway", "USS Voyager");
    
    std::cout << "Tabela apos insercoes:" << std::endl;
    fleet.printInOrder(std::cout);
    
    std::cout << "\n>> Status da Tabela:" << std::endl;
    std::cout << "Tamanho da Tabela: " << fleet.getTableSize() << std::endl;
    std::cout << "Numero de Colisoes: " << fleet.getCollissionsCount() << std::endl;
    std::cout << "Numero de Comparacoes: " << fleet.getComparisonsCount() << std::endl;

    std::string ship;
    assert(fleet.find("Kirk", ship) && ship == "USS Enterprise");
    assert(fleet.find("Picard", ship) && ship == "USS Enterprise-D");
    
    std::cout << "\n--- Fase 2: Promocoes e Desativacoes (Updates & Removals) ---\n";

    std::cout << "Atualizando a nave do Sisko usando update()...\n";
    fleet.update("Sisko", "USS Defiant");
    assert(fleet.find("Sisko", ship) && ship == "USS Defiant");
    
    std::cout << "Adicionando 'Archer' e sua 'Enterprise NX-01' usando operator[]...\n";
    fleet["Archer"] = "Enterprise NX-01";
    assert(fleet.find("Archer", ship) && ship == "Enterprise NX-01");
    
    std::cout << "O Kirk foi promovido! Atualizando sua nave para 'USS Enterprise-A'...\n";
    fleet["Kirk"] = "USS Enterprise-A";
    assert(fleet.find("Kirk", ship) && ship == "USS Enterprise-A");
    
    std::cout << "Desativando a nave de Janeway (removendo o registro)...\n";
    fleet.remove("Janeway");
    assert(!fleet.find("Janeway", ship));

    std::cout << "\nEstado final da frota:" << std::endl;
    fleet.printInOrder(std::cout);
}

/**
 * @brief Testa a capacidade de redimensionamento (rehash) e o tratamento de exceções.
 *
 * Este teste demonstra:
 * 1.  O rehash automático quando o fator de carga (`load factor`) é excedido.
 * 2.  O uso do método `rehash()` para forçar um redimensionamento manual.
 * 3.  O tratamento de exceções para chaves duplicadas (`insert`) e não encontradas (`update`, `const operator[]`).
 * 4.  O funcionamento do método `clear()`.
 */
void testRehashingAndExceptions() {
    printHeader("Teste de Rehash, Capacidade e Excecoes");
    
    // Tabela com tamanho 3 e fator de carga maximo de 1.0. O 4º elemento deve causar rehash.
    ChainedHashTable<int, std::string> testTable(3, 1.0f);
    
    std::cout << "\n--- Fase 1: Testando o Rehash Automatico ---\n";
    std::cout << "Tamanho inicial da tabela: " << testTable.getTableSize() << std::endl;
    
    testTable[10] = "Dez";
    testTable[20] = "Vinte";
    testTable[30] = "Trinta";
    testTable[40] = "Quarenta";
    testTable[50] = "Cinquenta";
    
    std::cout << "Tabela cheia (5/5)... Adicionando o proximo elemento para forcar o rehash.\n";
    testTable[60] = "Sessenta";
    
    std::cout << "Tamanho da tabela apos rehash: " << testTable.getTableSize() << std::endl;
    assert(testTable.getTableSize() > 3); // O tamanho deve ser o proximo primo > 5*2

    std::string value;
    assert(testTable.find(10, value) && value == "Dez");
    assert(testTable.find(40, value) && value == "Quarenta");
    std::cout << "Todos os elementos foram preservados apos o rehash.\n";

    std::cout << "\n--- Fase 2: Testando Excecoes ---\n";
    try {
        std::cout << "Tentando inserir chave duplicada (20)...\n";
        testTable.insert(20, "Vinte de novo");
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "Tentando atualizar chave inexistente (99)...\n";
        testTable.update(99, "Noventa e Nove");
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
    }

    std::cout << "\n--- Fase 3: Testando o metodo clear() ---\n";
    std::cout << "Limpando a tabela...\n";
    testTable.clear();
    assert(!testTable.find(10, value));
    assert(testTable.getCollissionsCount() == 0);
    std::cout << "Tabela limpa com sucesso. Tentando buscar elemento: " << std::boolalpha << testTable.find(10, value) << std::endl;
}

/**
 * @brief Testa a corretude do `const` e o comportamento do `const operator[]`.
 */
void testConstCorrectness() {
    printHeader("Teste de Corretude 'const'");

    const auto constTable = [] {
        ChainedHashTable<std::string, int> tempTable(5);
        tempTable["Terra"] = 3;
        tempTable["Marte"] = 4;
        tempTable["Jupiter"] = 5;
        return tempTable;
    }();
    
    std::cout << "Acessando 'Marte' em uma tabela constante: " << constTable["Marte"] << std::endl;
    assert(constTable["Marte"] == 4);

    try {
        std::cout << "Tentando acessar uma chave inexistente ('Plutao') em uma tabela constante...\n";
        int val = constTable["Plutao"]; // Deve lançar KeyNotFoundException
        assert(false);
    } catch(const std::exception& e) {
        std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
    }
    std::cout << "Teste de 'const' concluido com sucesso." << std::endl;
}

void testRehash() {
    printHeader("Teste de Rehash aplicando próximo primo");

    ChainedHashTable<int, char> testTable(5, 1.0);

    for (int i = 1; i <= 7; i++)
        testTable.insert(i, 'o');

    std::cout << "Table size: " << testTable.getTableSize() << std::endl;

    testTable.insert(0, '*');

    std::cout << "Table size: " << testTable.getTableSize() << std::endl;

    // next prime is 2 * 7 = 14 ==> 17
    assert(testTable.getTableSize() == 17);
}

int main() {
    testBasicFunctionality();
    testRehashingAndExceptions();
    testConstCorrectness();
    testRehash();
    
    std::cout << "\n" << std::string(70, '*') << "\n";
    std::cout << std::string(10, ' ') << "TODOS OS TESTES DA TABELA HASH FORAM CONCLUIDOS!" << std::string(10, ' ') << "\n";
    std::cout << std::string(70, '*') << std::endl;

    return 0;
}
#include "Trees/RedBlack/RedBlackTree.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <stdexcept>
#include <iomanip>

// Uma função auxiliar para deixar a saída dos testes mais organizada e bonita.
void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << std::string((70 - title.length()) / 2, ' ') << title << "\n";
    std::cout << std::string(70, '=') << std::endl;
}

/**
 * @brief Testa o ciclo de vida completo dos elementos na árvore.
 * * Este teste simula um cenário completo:
 * 1.  **Criação:** Insere vários elementos, construindo a árvore.
 * 2.  **Verificação:** Exibe a estrutura da árvore, a ordem dos elementos e as contagens de rotações/comparações.
 * 3.  **Modificação:** Usa tanto o método `update()` quanto o `operator[]` para alterar valores.
 * 4.  **Adição com `operator[]`:** Mostra que o operador de acesso também pode inserir novos elementos.
 * 5.  **Remoção:** Deleta vários nós para testar os diferentes casos de remoção e o rebalanceamento.
 */
void testComprehensiveLifecycle() {
    printHeader("Teste de Ciclo de Vida: A Sociedade da Arvore");
    RedBlackTree<std::string, int> fellowship;

    // --- Fase 1: Inserindo os personagens (e um vilão) ---
    std::cout << "\n--- Fase 1: Montando a Sociedade (Insercoes) ---\n";
    fellowship.insert("Gandalf", 9000);
    fellowship.insert("Aragorn", 8000);
    fellowship.insert("Legolas", 7000);
    fellowship.insert("Gimli", 6000);
    fellowship.insert("Frodo", 4000);
    fellowship.insert("Samwise", 5000);
    fellowship.insert("Sauron", 10000); // O antagonista

    std::cout << "Estrutura da Arvore (R = RED, B = BLACK):" << std::endl;
    fellowship.print();
    
    std::cout << "\nTravessia In-Order (deve estar em ordem alfabetica):" << std::endl;
    fellowship.printInOrder(std::cout);

    std::cout << "\nRotacoes iniciais apos insercoes: " << fellowship.getRotationsCount() << std::endl;
    std::cout << "Comparacoes iniciais: " << fellowship.getComparisonsCount() << std::endl;

    // Verifica se os elementos foram inseridos corretamente
    int powerLevel;
    assert(fellowship.find("Gandalf", powerLevel) && powerLevel == 9000);
    assert(fellowship.find("Sauron", powerLevel) && powerLevel == 10000);

    // --- Fase 2: Desenvolvimento dos personagens (Updates e operator[]) ---
    std::cout << "\n--- Fase 2: Desenvolvimento (Updates & operator[]) ---\n";
    std::cout << "Atualizando o poder do 'Sauron' para 12000 com o metodo update().\n";
    fellowship.update("Sauron", 12000);
    assert(fellowship.find("Sauron", powerLevel) && powerLevel == 12000);

    std::cout << "Acessando e atualizando o poder do 'Frodo' com o operator[].\n";
    assert(fellowship["Frodo"] == 4000);
    fellowship["Frodo"] = 4500; // Frodo ficou um pouco mais forte
    assert(fellowship["Frodo"] == 4500);

    std::cout << "Adicionando 'Bilbo' a aventura usando o operator[].\n";
    fellowship["Bilbo"] = 2000;
    assert(fellowship.find("Bilbo", powerLevel) && powerLevel == 2000);

    std::cout << "\nEstrutura da Arvore apos as atualizacoes:" << std::endl;
    fellowship.print();

    // --- Fase 3: A Sociedade se desfaz (Remocoes) ---
    std::cout << "\n--- Fase 3: A Sociedade se Desfaz (Remocoes) ---\n";
    std::cout << "Removendo 'Sauron' (o antagonista foi derrotado).\n";
    fellowship.remove("Sauron");
    assert(!fellowship.find("Sauron", powerLevel));

    std::cout << "Removendo 'Gimli' (para testar outro caso de remocao).\n";
    fellowship.remove("Gimli");
    assert(!fellowship.find("Gimli", powerLevel));

    std::cout << "Tentando remover um personagem que nao existe, 'Boromir'.\n";
    fellowship.remove("Boromir"); // Nao deve fazer nada nem quebrar a aplicacao.

    std::cout << "\nEstrutura Final da Arvore:" << std::endl;
    fellowship.print();
    std::cout << "\nTravessia Final In-Order:" << std::endl;
    fellowship.printInOrder(std::cout);
}

/**
 * @brief Testa casos de borda e o tratamento de exceções.
 *
 * Este teste verifica como a árvore se comporta em situações incomuns:
 * 1.  **Chave Duplicada:** Garante que a inserção de uma chave existente lança a exceção correta.
 * 2.  **Update Inexistente:** Garante que a tentativa de atualizar uma chave que não existe lança uma exceção.
 * 3.  **Limpeza Total:** Testa o método `clear()` e verifica se a árvore fica realmente vazia.
 */
void testEdgeCasesAndExceptions() {
    printHeader("Teste de Casos de Borda e Excecoes");
    RedBlackTree<int, std::string> numberTree;

    // --- Fase 1: Lidando com Chaves Duplicadas ---
    std::cout << "\n--- Fase 1: Tratando Insercao de Chave Duplicada ---\n";
    numberTree.insert(10, "Dez");
    try {
        std::cout << "Tentando inserir a chave 10 novamente...\n";
        numberTree.insert(10, "Dez Repetido");
        assert(false); // O teste deve falhar se esta linha for alcancada
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada com sucesso: " << e.what() << std::endl;
    }

    // --- Fase 2: Lidando com Update em Chave Inexistente ---
    std::cout << "\n--- Fase 2: Tratando Update em Chave Inexistente ---\n";
    try {
        std::cout << "Tentando atualizar a chave 99 que nao existe...\n";
        numberTree.update(99, "Noventa e Nove");
        assert(false); // O teste deve falhar se esta linha for alcancada
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada com sucesso: " << e.what() << std::endl;
    }

    // --- Fase 3: Testando a limpeza completa da arvore ---
    std::cout << "\n--- Fase 3: Testando o metodo clear() ---\n";
    numberTree.insert(20, "Vinte");
    numberTree.insert(5, "Cinco");
    std::cout << "Arvore antes de limpar:" << std::endl;
    numberTree.print();
    std::cout << "\nLimpando a arvore...\n";
    numberTree.clear();
    std::cout << "Arvore apos limpar (deve estar vazia):" << std::endl;
    numberTree.print();

    // Confirma que a árvore está vazia
    std::string value;
    assert(!numberTree.find(10, value));
    assert(!numberTree.find(20, value));
    assert(!numberTree.find(5, value));
    std::cout << "Arvore esta vazia, como esperado." << std::endl;
}

/**
 * @brief Testa a corretude do `const`, ou seja, a segurança em objetos constantes.
 * * Cria uma árvore constante e verifica se:
 * 1.  É possível ler dados usando `find()` e o `operator[]` constante.
 * 2.  O compilador impediria a escrita (verificado conceitualmente, pois um erro de compilação não pode ser testado em tempo de execução).
 */
void testConstCorrectness() {
    printHeader("Teste de Corretude 'const'");
    
    // Usamos uma lambda para criar e popular uma arvore temporaria,
    // que sera movida para uma instancia constante.
    const RedBlackTree<std::string, int> solarSystem = []() {
        RedBlackTree<std::string, int> temp;
        temp["Mercury"] = 1;
        temp["Venus"] = 2;
        temp["Earth"] = 3;
        temp["Mars"] = 4;
        temp["Jupiter"] = 5;
        return temp;
    }();

    std::cout << "Acessando elementos em uma Arvore Rubro-Negra constante...\n";
    assert(solarSystem["Earth"] == 3);
    assert(solarSystem["Mars"] == 4);

    std::cout << "Buscando por 'Venus' com find(): ";
    int planetNumber;
    if (solarSystem.find("Venus", planetNumber)) {
        std::cout << "Encontrado com o valor " << planetNumber << ". Verificando...\n";
        assert(planetNumber == 2);
    } else {
        std::cout << "Nao encontrado. O teste falhou.\n";
        assert(false);
    }
    
    // A linha a seguir causaria um erro de compilacao, que eh o comportamento esperado
    // para um objeto constante, provando que a seguranca de tipo esta funcionando.
    // solarSystem["Pluto"] = 9; // ERRO: a expressao precisa ser um l-value modificavel
    
    std::cout << "Teste de 'const' passou! A modificacao de dados e prevenida em tempo de compilacao." << std::endl;
}


// Funcao principal que executa todos os testes em sequencia.
int main() {
    testComprehensiveLifecycle();
    testEdgeCasesAndExceptions();
    testConstCorrectness();

    std::cout << "\n" << std::string(70, '*') << "\n";
    std::cout << std::string(10, ' ') << "TODOS OS TESTES DA ARVORE RUBRO-NEGRA FORAM CONCLUIDOS!" << std::string(10, ' ') << "\n";
    std::cout << std::string(70, '*') << std::endl;

    return 0;
}
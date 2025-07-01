#include "Trees/RedBlack/RedBlackTree.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <stdexcept>
#include <iomanip>

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << std::string((70 - title.length()) / 2, ' ') << title << "\n";
    std::cout << std::string(70, '=') << std::endl;
}

void testComprehensiveLifecycle() {
    printHeader("Teste de Ciclo de Vida: A Sociedade da Arvore");
    RedBlackTree<std::string, int> fellowship;

    std::cout << "\n--- Fase 1: Montando a Sociedade (Insercoes) ---\n";
    fellowship.insert("Gandalf", 9000);
    fellowship.insert("Aragorn", 8000);
    fellowship.insert("Legolas", 7000);
    fellowship.insert("Gimli", 6000);
    fellowship.insert("Frodo", 4000);
    fellowship.insert("Samwise", 5000);
    fellowship.insert("Sauron", 10000);

    std::cout << "Estrutura da Arvore (R = RED, B = BLACK):" << std::endl;
    fellowship.print();
    
    std::cout << "\nTravessia In-Order (deve estar em ordem alfabetica):" << std::endl;
    fellowship.printInOrder(std::cout);

    std::cout << "\nRotacoes iniciais apos insercoes: " << fellowship.getRotationsCount() << std::endl;
    std::cout << "Comparacoes iniciais: " << fellowship.getComparisonsCount() << std::endl;

    int powerLevel;
    assert(fellowship.find("Gandalf", powerLevel) && powerLevel == 9000);
    assert(fellowship.find("Sauron", powerLevel) && powerLevel == 10000);

    std::cout << "\n--- Fase 2: Desenvolvimento (Updates & operator[]) ---\n";
    std::cout << "Atualizando o poder do 'Sauron' para 12000 com o metodo update().\n";
    fellowship.update("Sauron", 12000);
    assert(fellowship.find("Sauron", powerLevel) && powerLevel == 12000);

    std::cout << "Acessando e atualizando o poder do 'Frodo' com o operator[].\n";
    assert(fellowship["Frodo"] == 4000);
    fellowship["Frodo"] = 4500;
    assert(fellowship["Frodo"] == 4500);

    std::cout << "Adicionando 'Bilbo' a aventura usando o operator[].\n";
    fellowship["Bilbo"] = 2000;
    assert(fellowship.find("Bilbo", powerLevel) && powerLevel == 2000);

    std::cout << "\nEstrutura da Arvore apos as atualizacoes:" << std::endl;
    fellowship.print();

    std::cout << "\n--- Fase 3: A Sociedade se Desfaz (Remocoes) ---\n";
    std::cout << "Removendo 'Sauron'.\n";
    fellowship.remove("Sauron");
    assert(!fellowship.find("Sauron", powerLevel));

    std::cout << "Removendo 'Gimli'.\n";
    fellowship.remove("Gimli");
    assert(!fellowship.find("Gimli", powerLevel));

    std::cout << "Tentando remover 'Boromir'.\n";
    fellowship.remove("Boromir");

    std::cout << "\nEstrutura Final da Arvore:" << std::endl;
    fellowship.print();
    std::cout << "\nTravessia Final In-Order:" << std::endl;
    fellowship.printInOrder(std::cout);
}

void testEdgeCasesAndExceptions() {
    printHeader("Teste de Casos de Borda e Excecoes");
    RedBlackTree<int, std::string> numberTree;

    std::cout << "\n--- Fase 1: Tratando Insercao de Chave Duplicada ---\n";
    numberTree.insert(10, "Dez");
    try {
        std::cout << "Tentando inserir a chave 10 novamente...\n";
        numberTree.insert(10, "Dez Repetido");
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada com sucesso: " << e.what() << std::endl;
    }

    std::cout << "\n--- Fase 2: Tratando Update em Chave Inexistente ---\n";
    try {
        std::cout << "Tentando atualizar a chave 99...\n";
        numberTree.update(99, "Noventa e Nove");
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Excecao esperada capturada com sucesso: " << e.what() << std::endl;
    }

    std::cout << "\n--- Fase 3: Testando o metodo clear() ---\n";
    numberTree.insert(20, "Vinte");
    numberTree.insert(5, "Cinco");
    std::cout << "Arvore antes de limpar:" << std::endl;
    numberTree.print();
    std::cout << "\nLimpando a arvore...\n";
    numberTree.clear();
    std::cout << "Arvore apos limpar:" << std::endl;
    numberTree.print();

    std::string value;
    assert(!numberTree.find(10, value));
    assert(!numberTree.find(20, value));
    assert(!numberTree.find(5, value));
    std::cout << "Arvore esta vazia, como esperado." << std::endl;
}

void testConstCorrectness() {
    printHeader("Teste de Corretude 'const'");
    
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
        std::cout << "Encontrado com o valor " << planetNumber << ".\n";
        assert(planetNumber == 2);
    } else {
        std::cout << "Nao encontrado.\n";
        assert(false);
    }

    std::cout << "Teste de 'const' passou!" << std::endl;
}

int main() {
    testComprehensiveLifecycle();
    testEdgeCasesAndExceptions();
    testConstCorrectness();

    std::cout << "\n" << std::string(70, '*') << "\n";
    std::cout << std::string(10, ' ') << "TODOS OS TESTES DA ARVORE RUBRO-NEGRA FORAM CONCLUIDOS!" << std::string(10, ' ') << "\n";
    std::cout << std::string(70, '*') << std::endl;

    return 0;
}

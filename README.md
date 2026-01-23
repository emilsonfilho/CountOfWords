# CountOfWords 📊

Ferramenta de alto desempenho desenvolvida em C++ para contagem de frequência de palavras em arquivos de texto. 

O objetivo principal deste projeto é realizar um estudo comparativo de eficiência (tempo de execução e consumo de memória) entre diferentes implementações de estruturas de dados clássicas: Árvores Balanceadas e Tabelas Hash.

## 🚀 Estruturas de Dados Implementadas

O sistema permite processar o mesmo texto utilizando diferentes "motores" de armazenamento:

1.  **Árvore AVL** (`AVLTree`): Árvore binária de busca auto-balanceável.
2.  **Árvore Rubro-Negra** (`RedBlackTree`): Outra variante de árvore balanceada, otimizada para inserções.
3.  **Tabela Hash - Encadeamento** (`ChainedHashTable`): Tratamento de colisões usando listas encadeadas.
4.  **Tabela Hash - Endereçamento Aberto** (`OpenAddressingHashTable`): Tratamento de colisões sondagem linear/quadrática.

## ⚙️ Arquitetura e Design Patterns

O projeto foi construído seguindo princípios de Engenharia de Software e Padrões de Projeto para garantir extensibilidade e organização:

* **Factory Pattern:** Utilizado (`DictionaryFactory`) para instanciar a estrutura de dados correta em tempo de execução sem acoplar o código principal.
* **Visitor Pattern:** Implementado (`ReportDataCollectorVisitor`) para percorrer as estruturas e coletar dados para relatórios sem expor a lógica interna de cada estrutura.
* **Singleton:** Utilizado para gerenciamento global de configurações, como o `LocaleManager`.
* **Strategy:** O uso da interface `IDictionary` permite que o analisador troque a estratégia de armazenamento (Árvore ou Hash) transparentemente.

## 📂 Estrutura do Repositório

* `src/` e `include/`: Código fonte separado por responsabilidades (CLI, Trees, HashTables, FileProcessor).
* `input/`: Textos utilizados para testes de carga (ex: *Dom Casmurro*, *Bíblia*, *Sherlock Holmes*).
* `output/`: Resultados gerados contendo a frequência das palavras.
* `docs/uml/`: Diagramas de classe e arquitetura do sistema.

## 🛠️ Como Compilar e Rodar

### Pré-requisitos
* Compilador C++ (G++ com suporte a C++17 ou superior).
* Make.

### Compilação
Utilize o `Makefile` incluído na raiz para gerar os binários:

```bash
make
```

Isso irá gerar os executáveis dentro da pasta `bin/`, correspondentes a cada estrutura (ex: `AVL`, `RedBlack`, `Chained`, `OpenAddressing`).

### Execução

Para rodar a análise, execute o binário desejado passando o arquivo de entrada:

```bash
./bin/AVL input/dom-casmurro.txt output/resultado_avl.txt
```

O programa irá ler o arquivo, processar a contagem de palavras, exibir o tempo de execução no terminal e salvar a lista de frequências no arquivo de saída.

**Disciplina** Estrutura de Dados Avançada

Feito com ❤️ by **Emilson Filho**

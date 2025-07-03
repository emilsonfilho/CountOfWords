#include "Factory/DictionaryFactory.hpp"
#include "FileProcessor/FileProcessor.hpp"

int main() {
    std::unique_ptr<IDictionary<std::string, int>> dict = DictionaryFactory<std::string, int>::createDictionary(StringHandler::toDictionaryType("dictionary_avl"));

    dict->insert("Emilson", 8);
    (*dict)["Emilson"]++;
    (*dict)["Alessandra"]++;

    dict->printInOrder(std::cout);

    FileProcessor fp("text.txt");

    fp.normalizeWord()
}
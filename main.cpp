#include "Factory/DictionaryFactory.hpp"
#include "FileProcessor/FileProcessor.hpp"
#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"

int main() {
    std::unique_ptr<IDictionary<std::string, int>> dict = DictionaryFactory<std::string, int>::createDictionary(StringHandler::toDictionaryType("dictionary_avl"));

    dict->insert("Emilson", 8);
    (*dict)["Emilson"]++;
    (*dict)["Alessandra"]++;

    dict->printInOrder(std::cout);

    FileProcessor fp("text");

    for (std::string& word : fp.words) {
        std::cout << word << "\n";
    }
    std::cout << std::endl;

    WordFrequencyAnalyzer wfa;
    ReportData result = wfa.analyze(dict, fp.words);

    cout << result.buildTime << std::endl;
}
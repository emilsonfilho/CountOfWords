#include "Factory/DictionaryFactory.hpp"
#include "FileProcessor/FileProcessor.hpp"
#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"
#include "Utils/Casting/Casting.hpp"
#include "Reports/ReportWriter.hpp"

int main() {
    std::unique_ptr<IDictionary<std::string, int>> dict = DictionaryFactory<std::string, int>::createDictionary(Casting::toDictionaryType("dictionary_avl"));

    dict->insert("Emilson", 8);
    (*dict)["Emilson"]++;
    (*dict)["Alessandra"]++;

    dict->printInOrder(std::cout);

    FileProcessor fp("crime_and_punishment");

    for (std::string& word : fp.words) {
        std::cout << word << "\n";
    }
    std::cout << std::endl;

    ReportData result = WordFrequencyAnalyzer().analyze(std::move(dict), fp);

    std::cout << result.buildTime.count() << std::endl;

    ReportWriter().exportReport(result, std::cout, std::move(dict));
}
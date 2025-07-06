#include <fstream>

#include "Factory/DictionaryFactory.hpp"
#include "FileProcessor/FileProcessor.hpp"
#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"
#include "Utils/Casting/Casting.hpp"
#include "Reports/ReportWriter.hpp"

int main() {
    std::ofstream outFile("output/crime_and_punishment.txt");
    std::unique_ptr<IDictionary<std::string, int>> dict = DictionaryFactory<std::string, int>::createDictionary(Casting::toDictionaryType("dictionary_avl"));

    dict->insert("Emilson", 8);
    (*dict)["Emilson"]++;
    (*dict)["Alessandra"]++;

    FileProcessor fp("crime_and_punishment");

    ReportData result = WordFrequencyAnalyzer::analyze(dict.get(), fp);

    std::cout << result.buildTime.count() << std::endl;

    ReportWriter().exportReport(result, outFile, dict.get());
}
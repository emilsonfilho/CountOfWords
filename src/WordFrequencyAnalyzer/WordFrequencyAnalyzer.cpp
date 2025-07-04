#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"

#include "Utils/Timer/Timer.hpp"
#include "Visitor/ReportDataCollectorVisitor.hpp"

ReportData WordFrequencyAnalyzer::analyze(
    std::unique_ptr<IDictionary<std::string, int>> dictionary,
    const std::vector<std::string>& words
) const {
    ReportData report;

    Timer timer;
    timer.start();

    long wordsCount = 0;
    for (const std::string& word : words) {
        (*dictionary)[word]++;
        wordsCount++;
    }

    timer.stop();

    /**
     * Acredito que isso não devia ser feito dessa maneira e era para ser 
     * possível receber o valor sem ser lvalue modificável
     * Além disso, está dando erro de conversão. Isso se dá pelo fato
     * de que eu acho que a conversão lá em AVLTree e as outras classes estão
     * erradas em assumir que receberão objetos de IDictionary
     */
    ReportDataCollectorVisitor<std::string, int> visitor(report); 
    dictionary->accept(visitor);
    report.buildTime = timer.duration();
    report.totalWordsProcessed = wordsCount;

    return report;
}
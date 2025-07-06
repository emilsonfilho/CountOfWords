#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"

#include "Utils/Timer/Timer.hpp"
#include "Visitor/ReportDataCollectorVisitor.hpp"
#include "Utils/Strings/StringHandler.hpp"

ReportData WordFrequencyAnalyzer::analyze(
    IDictionary<std::string, int>* dictionary,
    const FileProcessor& fileProcessor
) {
    ReportData report;

    Timer timer;
    timer.start();

    long wordsCount = 0;
    report.maxKeyLength = 0;
    for (const std::string& word : fileProcessor.words) {
        (*dictionary)[word]++;
        wordsCount++;
        report.maxKeyLength = std::max(report.maxKeyLength, StringHandler::size(word));
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
    report.filename = fileProcessor.path;

    return report;
}
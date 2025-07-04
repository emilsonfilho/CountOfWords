#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"

#include "Utils/Timer/Timer.hpp"
#include "Visitor/ReportDataCollectorVisitor.hpp"

ReportData WordFrequencyAnalyzer::analyze(
    std::unique_ptr<IDictionary<std::string, int>> dictionary,
    const vector<std::string>& words
) const {
    ReportData report;

    Timer timer;
    timer.start();

    long wordsCount = 0;
    for (const std::string& word : words) {
        dictionary[word]++;
        wordsCount++;
    }

    timer.stop();

    dictionary->accept(ReportDataCollectorVisitor(report));
    report.buildTime = timer.duration();
    report.totalWordsProcessed = wordsCount;

    return report;
}
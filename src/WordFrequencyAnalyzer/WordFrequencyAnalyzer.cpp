#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"

#include <cmath>

#include "Utils/Strings/StringHandler.hpp"
#include "Utils/Timer/Timer.hpp"
#include "Visitor/ReportDataCollectorVisitor.hpp"

ReportData
WordFrequencyAnalyzer::analyze(IDictionary<LexicalStr, size_t> *dictionary,
                               const FileProcessor &fileProcessor) {
  ReportData report;

  Timer timer;
  timer.start();

  long wordsCount = 0;
  report.maxKeyLength = 0;
  for (const std::string &word : fileProcessor.words) {
    (*dictionary)[word]++;
    wordsCount++;
    report.maxKeyLength =
        std::max(report.maxKeyLength, StringHandler::size(word));
  }

  timer.stop();

  ReportDataCollectorVisitor<LexicalStr, size_t> visitor(report);
  dictionary->accept(visitor);
  report.buildTime = timer.duration();
  report.totalWordsProcessed = wordsCount;
  report.filename = fileProcessor.path;
  report.memoryUsage = std::round(dictionary->getMemoryUsage() / 1024);

  return report;
}
#include "CLI/CLIHandler.hpp"

#include <fstream>

#include "Configs/Locale/CollateCompare/CollateCompare.hpp"
#include "Configs/Path.hpp"
#include "Factory/DictionaryFactory.hpp"
#include "FileProcessor/FileProcessor.hpp"
#include "Reports/ReportWriter.hpp"
#include "Utils/Casting/Casting.hpp"
#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"

CLIHandler::CLIHandler(int argc, char **argv) {
  quantityArguments = argc;

  if (argc > 2) { // no segfault
    options.filename = argv[2];
    options.inputDict = argv[1];
  }
}

bool CLIHandler::validOptions() {
  try {
    if (quantityArguments <= 2)
      return false;

    options.dictType = Casting::toDictionaryType(options.inputDict);
    return true;
  } catch (const DictionaryTypeNotFoundException &e) {
    return false;
  }
}

int CLIHandler::execute() {
  try {
    FileProcessor fp(options.filename);

    std::ofstream outFile(outputPath + options.filename);
    std::unique_ptr<IDictionary<std::string, size_t, std::hash<std::string>, CollateCompare>> dict =
        DictionaryFactory<std::string, size_t>::createDictionary(options.dictType);

    ReportData report = WordFrequencyAnalyzer::analyze(dict.get(), fp);

    ReportWriter::exportReport(report, outFile, dict.get());

    return 0;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
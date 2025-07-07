#include "CLI/CLIHandler.hpp"

#include <fstream>

#include "Configs/Path.hpp"
#include "Factory/DictionaryFactory.hpp"
#include "FileProcessor/FileProcessor.hpp"
#include "WordFrequencyAnalyzer/WordFrequencyAnalyzer.hpp"
#include "Utils/Casting/Casting.hpp"
#include "Reports/ReportWriter.hpp"


CLIHandler::CLIHandler(int argc, char** argv) {
    quantityArguments = argc;

    if (argc > 2) { // no segfault
        options.filename = argv[2];
        options.inputDict = argv[1];
    }
}

bool CLIHandler::validOptions() {
    try {
        options.dictType = Casting::toDictionaryType(options.inputDict);
        return true;
    } catch (const DictionaryTypeNotFoundException& e) {
        return false;
    }
}

int CLIHandler::execute() {
    try {
        std::ofstream outFile(outputPath + options.filename);
        std::unique_ptr<IDictionary<std::string, int>> dict = DictionaryFactory<std::string, int>::createDictionary(options.dictType);

        FileProcessor fp(options.filename);

        ReportData report = WordFrequencyAnalyzer::analyze(dict.get(), fp);

        ReportWriter::exportReport(report, outFile, dict.get());

        return 0;
    } catch (const std::exception& e) {
        return 1;
    }
}
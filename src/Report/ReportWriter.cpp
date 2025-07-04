#include "Reports/ReportWriter.hpp"

#include <string>

void ReportWriter::printLine(std::ostream& out) const {
    out << std::string(80, '=') << '\n';
}

void ReportWriter::exportReport(const ReportData& reportData, std::ostream& out, std::unique_ptr<IDictionary<std::string, int>> dict) {
    printLine(out);
    out << "Count of Words: Data Structure Edition - Output Report\n";
    out << "Arquivo Analisado: " << reportData.filename << '\n';
    out << "Estrutura de Dados: " << reportData.dictionaryType << '\n';

    printLine(out);
}
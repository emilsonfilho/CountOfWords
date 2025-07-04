#include "Reports/ReportWriter.hpp"

#include <string>

#include "Utils/Timer/Timer.hpp"

void ReportWriter::printLine(std::ostream& out) const {
    out << std::string(80, '=') << '\n';
}

void ReportWriter::exportReport(const ReportData& reportData, std::ostream& out, IDictionary<std::string, int>* dict) {
    printLine(out);
    out << "Count of Words: Data Structure Edition - Output Report\n";
    printLine(out);
    out << "Arquivo Analisado: " << reportData.filename << '\n';
    out << "Estrutura de Dados: " << reportData.dictionaryType << '\n';
    out << "Data de execução: " << Timer::getCurrentDateTime() << '\n';

    out << '\n';

    printLine(out);
    out << "Tabela de Frequências\n";
    printLine(out);
    out << "Palavra" << std::string(reportData.maxKeyLength - 7, ' ') << "| " << "Frequência";
    dict->printInOrder(out);

    out << '\n';

    printLine(out);
    out << "Métricas de Desempenho\n"; // refatorar isso para uma função que printa um cabeçalho
    printLine(out);
    out << "Tempo total (ms): " << reportData.buildTime.count() << '\n';
    out << "Número de comparações: " << reportData.comparisons << '\n';
    out << "Número de " << reportData.specificMetric.first << ": " << reportData.specificMetric.second << '\n';
}
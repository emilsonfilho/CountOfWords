#include "Reports/ReportWriter.hpp"

#include <string>

#include "Utils/Timer/Timer.hpp"

void ReportWriter::printLine(std::ostream& out) const {
    out << std::string(80, '=') << '\n';
}

void ReportWriter::printHeader(const std::string& title, std::ostream& out) const {
    printLine(out);
    out << title << "\n";
    printLine(out);
}

void ReportWriter::exportReport(const ReportData& reportData, std::ostream& out, IDictionary<std::string, int>* dict) {
    printHeader("Count of Words: Data Structure Edition - Output Report", out);
    out << "Arquivo Analisado: " << reportData.filename << '\n';
    out << "Estrutura de Dados: " << reportData.dictionaryType << '\n';
    out << "Data de execução: " << Timer::getCurrentDateTime() << '\n';

    out << std::endl;

    printHeader("Tabela de Frequências", out);
    std::cout << "Valor maximo de chave: " << reportData.maxKeyLength << std::endl;
    out << "Palavra" << std::string(reportData.maxKeyLength - 6, ' ') << "| " << "Frequência\n";
    dict->printInOrder(out);

    out << '\n';

    printHeader("Métricas de Desempenho", out);
    out << "Tempo total (ms): " << reportData.buildTime.count() << '\n';
    out << "Número de comparações: " << reportData.comparisons << '\n';
    out << "Número de " << reportData.specificMetric.first << ": " << reportData.specificMetric.second << '\n';
}
#ifndef FILE_PROCESSOR_EXCEPTIONS_HPP
#define FILE_PROCESSOR_EXCEPTIONS_HPP

#include <stdexcept>

class LocaleNotFoundException : public std::runtime_error {
public:
    explicit LocaleNotFoundException()
        : std::runtime_error(
            std::string("Locale não disponível no sistema. Rode as seguintes linhas de comando:\n")
            + "1. sudo locale-gen pt_BR.utf8\n"
            + "2. sudo update-locale\n"
            + "Depois, execute o programa novamente"
        ) {}
};

#endif
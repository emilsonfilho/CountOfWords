#ifndef CLI_EXCEPTIONS_HPP
#define CLI_EXCEPTIONS_HPP

#include <stdexcept>

class ArgumentsInvalidException : public std::invalid_argument{
public:
  explicit ArgumentsInvalidException()
      : std::invalid_argument(std::string("Argumentos inválidos!\n")
              + "O comando deve ser dado na seguinte forma:\n"
              + "freq [tipo] [nome_arquivo.txt]\n"
              + "As opções disponíveis são: \n"
              + "dictionary_avl\n"
              + "dictionary_redblack\n"
              + "dictionary_chained\n"
              + "dictionary_open") {}
};

#endif
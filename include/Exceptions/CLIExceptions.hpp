#ifndef CLI_EXCEPTIONS_HPP
#define CLI_EXCEPTIONS_HPP

#include <stdexcept>

/**
 * @class ArgumentsInvalidException
 * @brief Exception thrown when command-line arguments are invalid.
 *
 * This exception is used to signal that the user has provided incorrect arguments
 * when executing the program. It inherits from `std::invalid_argument` and provides
 * a predefined error message guiding the user on the correct usage format.
 *
 * Expected format:
 * @code
 * freq [tipo] [nome_arquivo.txt]
 * @endcode
 *
 * Supported dictionary types:
 * - dictionary_avl
 * - dictionary_redblack
 * - dictionary_chained
 * - dictionary_open
 */
class ArgumentsInvalidException : public std::invalid_argument {
public:
    /**
     * @brief Constructs the exception with a predefined detailed message.
     */
    explicit ArgumentsInvalidException() : std::invalid_argument(std::string("Argumentos inválidos!\n")
              + "O comando deve ser dado na seguinte forma:\n"
              + "freq [tipo] [nome_arquivo.txt]\n"
              + "As opções disponíveis são: \n"
              + "dictionary_avl\n"
              + "dictionary_redblack\n"
              + "dictionary_chained\n"
              + "dictionary_open") {}
};

#endif
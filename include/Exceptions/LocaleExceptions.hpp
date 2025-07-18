#ifndef FILE_PROCESSOR_EXCEPTIONS_HPP
#define FILE_PROCESSOR_EXCEPTIONS_HPP

#include <stdexcept>

/**
 * @class LocaleNotFoundException
 * @brief Exception thrown when the required locale is not available on the
 * system.
 *
 * This class inherits from std::runtime_error and is used to indicate that
 * the system is missing the necessary locale configuration to run the program
 * properly. The error message includes suggested terminal commands to generate
 * and update the locale.
 */
class LocaleNotFoundException : public std::runtime_error {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the exception with a message guiding the user to generate the
   * missing locale.
   */
  explicit LocaleNotFoundException()
      : std::runtime_error(std::string("Locale não disponível no sistema. Rode "
                                       "as seguintes linhas de comando:\n") +
                           "1. sudo locale-gen pt_BR.utf8\n" +
                           "2. sudo update-locale\n" +
                           "Depois, execute o programa novamente") {}
};

#endif
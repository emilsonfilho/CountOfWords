#ifndef CLI_OPTIONS_HPP
#define CLI_OPTIONS_HPP

#include <string>

#include "Factory/DictionaryType.hpp"

/**
 * @struct CLIOptions
 * @brief Stores the command-line options provided by the user.
 *
 * This structure encapsulates the necessary parameters passed via the CLI to
 * configure the program's behavior, including input file and dictionary
 * settings.
 */
struct CLIOptions {
  /**
   * @brief Path to the file to be processed.
   */
  std::string filename;

  /**
   * @brief Path to the dictionary input file, if any.
   */
  std::string inputDict;

  /**
   * @brief Type of dictionary to be used in the program.
   */
  DictionaryType dictType;
};

#endif
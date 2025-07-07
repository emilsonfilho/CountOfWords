#ifndef CLI_HANDLER_HPP
#define CLI_HANDLER_HPP

#include "CLI/CLIOptions.hpp"

/**
 * @class CLIHandler
 * @brief Handles parsing and validation of command-line arguments.
 *
 * This class is responsible for interpreting the arguments passed to the
 * program, validating them, and initiating the execution based on the provided
 * options.
 */
class CLIHandler {
  /**
   * @brief Stores the parsed command-line options.
   */
  CLIOptions options;

  /**
   * @brief Number of arguments passed to the program.
   */
  int quantityArguments;

public:
  /**
   * @brief Constructs a CLIHandler and parses command-line arguments.
   * @param argc Number of command-line arguments.
   * @param argv Array of argument strings.
   */
  CLIHandler(int argc, char **argv);

  /**
   * @brief Validates the parsed command-line options.
   * @return true if options are valid, false otherwise.
   */
  bool validOptions();

  /**
   * @brief Executes the program logic based on parsed options.
   * @return Exit code of the program execution.
   */
  int execute();
};

#endif
#ifndef FILE_EXCEPTIONS_HPP
#define FILE_EXCEPTIONS_HPP

#include <stdexcept>

/**
 * @class FileNotFoundException
 * @brief Custom exception for file-not-found errors.
 *
 * This class inherits from std::out_of_range and is used to signal
 * that a file was not found during program execution.
 */
class FileNotFoundException : public std::out_of_range {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the exception with the message "File not found."
   */
  explicit FileNotFoundException(const std::string &filename)
      : std::out_of_range("File " + filename + " not found.") {}
};

#endif
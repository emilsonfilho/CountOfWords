#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <locale>
#include <string>
#include <vector>

/**
 * @class FileProcessor
 * @brief Responsible for reading and processing words from a file.
 *
 * This class reads the contents of a file, normalizes each word, and stores
 * them in a vector. It also configures locale settings to properly handle text
 * normalization.
 */
class FileProcessor {
  std::locale loc; ///< Locale used for word normalization.

  /**
   * @brief Normalizes a given word.
   *
   * Converts the word to lowercase using the configured locale
   * and removes trailing punctuation characters.
   *
   * @param word The word to normalize.
   * @return The normalized word.
   */
  std::vector<std::string> tokenize(const std::string &text) const;

  /**
   * @brief Normalizes a word by trimming leading/trailing underscores and converting it to lowercase.
   * @param word The word to be normalized.
   * @return The normalized string.
   */
  std::string normalize(const std::string &word) const;

  /**
   * @brief Checks if a character is an underscore.
   * @param ch The character to check.
   * @return `true` if the character is an underscore, `false` otherwise.
   */
  bool isUnderscore(char ch) const;
public:
  std::string path; ///< Full path to the input file.
  std::vector<std::string>
      words; //< Vector containing all normalized words read from the file.

  /**
   * @brief Constructs a FileProcessor and processes the file.
   *
   * Sets the file path, checks if the file and locale are available,
   * reads each word from the file, normalizes it, and stores it.
   *
   * @param filename Name of the file to be processed (without path).
   * @throws FileNotFoundException If the file cannot be opened.
   * @throws LocaleNotFoundException If the locale cannot be set on the system.
   */
  FileProcessor(const std::string &filename);
};

#endif
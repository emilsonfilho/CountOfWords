#ifndef KEY_EXCEPTIONS_HPP
#define KEY_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

/**
 * @class KeyAlreadyExistsException
 * @brief Exception thrown when attempting to insert a key that already exists
 * in a dictionary.
 *
 * This exception is derived from std::runtime_error and is used to indicate
 * that a key being inserted into a dictionary or similar data structure
 * already exists.
 *
 * Example usage:
 * @code
 * try {
 *     dictionary.insert(key, value);
 * } catch (const KeyAlreadyExistsException& e) {
 *     std::cerr << e.what() << std::endl;
 * }
 * @endcode
 */
class KeyAlreadyExistsException : public std::runtime_error {
public:
  explicit KeyAlreadyExistsException()
      : std::runtime_error("Key already exists in the dictionary.") {}
};

/**
 * @class KeyNotFoundException
 * @brief Exception thrown when a key is not found in a dictionary or map.
 *
 * This exception is derived from std::runtime_error and is used to indicate
 * that an operation attempted to access a key that does not exist in the
 * dictionary or map.
 *
 * Example usage:
 * @code
 * try {
 *     throw KeyNotFoundException();
 * } catch (const KeyNotFoundException& e) {
 *     std::cerr << e.what() << std::endl;
 * }
 * @endcode
 */
class KeyNotFoundException : public std::runtime_error {
public:
  explicit KeyNotFoundException()
      : std::runtime_error("Key not found in the dictionary.") {}
};

#endif

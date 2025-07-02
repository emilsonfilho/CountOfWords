#ifndef FACTORY_EXCEPTIONS_HPP
#define FACTORY_EXCEPTIONS_HPP

#include <stdexcept>

/**
 * @class DictionaryTypeNotFound
 * @brief Exception thrown when a requested dictionary type is not found in the factory.
 *
 * This class inherits from std::out_of_range. It is used to signal an error
 * when an attempt is made to create a dictionary with a type name that the
 * factory does not recognize.
 */
class DictionaryTypeNotFound : public std::out_of_range {
public:
    /**
     * @brief Constructs the exception object.
     *
     * Initializes the base class std::out_of_range with a default error message.
     * @post The exception object is created with the message "Dictionary type not found.".
     */
    explicit DictionaryTypeNotFound()
        : std::out_of_range("Dictionary type not found.") {}
};

#endif
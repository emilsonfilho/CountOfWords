#ifndef FILE_EXCEPTIONS_HPP
#define FILE_EXCEPTIONS_HPP

#include <stdexcept>

class FileNotFoundException : public std::out_of_range {
public:
    /**
     * @brief Constructs the exception object.
     *
     * Initializes the base class std::out_of_range with a default error message.
     * @post The exception object is created with the message "Dictionary type not found.".
     */
    explicit FileNotFoundException()
        : std::out_of_range("File not found.") {}
};

#endif
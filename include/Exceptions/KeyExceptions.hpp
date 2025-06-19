#ifndef KEY_EXCEPTIONS_HPP
#define KEY_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class KeyAlreadyExistsException : public std::runtime_error {
public:
    explicit KeyAlreadyExistsException()
        : std::runtime_error("Key already exists in the dictionary.") {}
};

class KeyNotFoundException : public std::runtime_error {
public:
    explicit KeyNotFoundException()
        : std::runtime_error("Key not found in the dictionary.") {}
}

#endif

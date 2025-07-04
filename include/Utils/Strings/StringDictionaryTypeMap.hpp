#ifndef STRING_DICTIONARY_TYPE_HPP
#define STRING_DICTIONARY_TYPE_HPP

#include <unordered_map>
#include <string>

#include "Factory/DictionaryType.hpp"

/**
 * @brief A constant map to convert string identifiers to DictionaryType enums.
 *
 * This unordered_map provides a convenient and efficient way to look up the
 * corresponding DictionaryType enum value from a human-readable string. It is
 * typically used to parse user input or configuration settings to determine
 * which dictionary implementation should be instantiated by a factory.
 */
const std::unordered_map<std::string, DictionaryType> stringDictionaryTypeMap = {
    {"dictionary_avl", DictionaryType::AVL},
    {"dictionary_redblack", DictionaryType::RedBlack},
    {"dictionary_chained", DictionaryType::Chained},
    {"dictionary_open", DictionaryType::OpenAddressing}
};

#endif
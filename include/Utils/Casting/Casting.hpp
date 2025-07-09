#ifndef CASTING_HPP
#define CASTING_HPP

#include "Dictionary/IDictionary.hpp"

namespace Casting {
/**
 * @brief Casts a concrete dictionary implementation to its constant IDictionary interface.
 * @namespace Casting
 * @tparam Key The key type of the dictionary.
 * @tparam Value The value type of the dictionary.
 * @tparam Impl The concrete dictionary implementation type, which must inherit from IDictionary<Key, Value>.
 * @param impl The dictionary implementation object to be cast.
 * @return A constant reference to the IDictionary interface of the provided implementation.
 */
template <typename Key, typename Value, typename Impl>
const IDictionary<Key, Value> &toIDictionary(const Impl &impl);

/**
 * @brief Converts a string identifier to a DictionaryType enum.
 *
 * This function attempts to find the given string `str` as a key in the
 * global `stringDicitionaryTypeMap`. If successful, it returns the
 * corresponding `DictionaryType` value.
 *
 * @param str The string representation of the dictionary type to convert.
 * @return The corresponding `DictionaryType` enum value.
 * @throw DictionaryTypeNotFoundException if the string does not correspond to a
 * valid dictionary type in the map.
 */
DictionaryType toDictionaryType(const std::string &str);
} // namespace Casting

#include "Utils/Casting/Casting.impl.hpp"

#endif
#ifndef DICTIONARY_TYPE_HPP
#define DICTIONARY_TYPE_HPP

/**
 * @brief Defines the types of dictionary data structures available.
 *
 * This enumeration is used to uniquely identify the different concrete
 * implementations of the dictionary interface, often used by a factory
 * to determine which object to create.
 */
enum class DictionaryType { AVL, RedBlack, Chained, OpenAddressing };

#endif
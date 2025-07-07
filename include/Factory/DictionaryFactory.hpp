#ifndef DICTIONARY_FACTORY_HPP
#define DICTIONARY_FACTORY_HPP

#include <memory>

#include "Dictionary/IDictionary.hpp"
#include "Exceptions/FactoryExceptions.hpp"
#include "Factory/DictionaryType.hpp"
#include "HashTables/Chained/ChainedHashTable.hpp"
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"
#include "Trees/AVL/AVLTree.hpp"
#include "Trees/RedBlack/RedBlackTree.hpp"

/**
 * @class DictionaryFactory
 * @brief A factory class for creating instances of dictionary data structures.
 *
 * This class provides a static method to create different implementations of
 * the IDictionary interface based on a string identifier. This encapsulates the
 * instantiation logic and promotes loose coupling.
 *
 * @tparam Key The type of the keys in the dictionary.
 * @tparam Value The type of the values in the dictionary.
 */
template <typename Key, typename Value, typename Compare = std::less<Key>> class DictionaryFactory {
public:
  /**
   * @brief Creates a dictionary instance based on the specified type.
   *
   * This static factory method returns a pointer to a new dictionary object
   * that implements the IDictionary interface. The concrete type of the object
   * is determined by the `dictType` string.
   *
   * @param dictType A string specifying the dictionary type to create.
   * Valid options are:
   * - "dictionary_avl"
   * - "dictionary_redblack"
   * - "dictionary_chained"
   * - "dictionary_open"
   * @return IDictionary<Key, Value>* A pointer to the newly created dictionary
   * instance. The caller is responsible for deleting this object.
   * @throw DictionaryTypeNotFoundException If the `dictType` does not match any
   * known type.
   */
  static std::unique_ptr<IDictionary<Key, Value>>
  createDictionary(DictionaryType dictType) {
    switch (dictType) {
    case DictionaryType::AVL:
      return std::make_unique<AVLTree<Key, Value, Compare>>();
    case DictionaryType::RedBlack:
      return std::make_unique<RedBlackTree<Key, Value, Compare>>();
    case DictionaryType::Chained:
      return std::make_unique<ChainedHashTable<Key, Value>>();
    case DictionaryType::OpenAddressing:
      return std::make_unique<OpenAddressingHashTable<Key, Value>>();
    default:
      throw DictionaryTypeNotFoundException();
    }
  }
};

#endif
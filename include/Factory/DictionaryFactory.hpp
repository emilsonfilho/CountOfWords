#ifndef DICTIONARY_FACTORY_HPP
#define DICTIONARY_FACTORY_HPP

#include "Dictionary/IDictionary.hpp"
#include "Trees/AVL/AVLTree.hpp"
#include "Trees/RedBlack/RedBlackTree.hpp"
#include "HashTables/Chained/ChainedHashTable.hpp"
#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"
#include "Exceptions/FactoryExceptions.hpp"

/**
 * @class DictionaryFactory
 * @brief A factory class for creating instances of dictionary data structures.
 *
 * This class provides a static method to create different implementations of the
 * IDictionary interface based on a string identifier. This encapsulates the
 * instantiation logic and promotes loose coupling.
 *
 * @tparam Key The type of the keys in the dictionary.
 * @tparam Value The type of the values in the dictionary.
 */
template <typename Key, typename Value>
class DictionaryFactory {
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
     * - "avl_dictionary"
     * - "redblack_dictionary"
     * - "chained_dictionary"
     * - "open_dictionary"
     * @return IDictionary<Key, Value>* A pointer to the newly created dictionary instance.
     * The caller is responsible for deleting this object.
     * @throw DictionaryTypeNotFound If the `dictType` does not match any known type.
     */
    static IDictionary<Key, Value>* createDictionary(const std::string& dictType) {
        if (dictType == "avl_dictionary")
            return new AVLTree<Key, Value>();

        if (dictType == "redblack_dictionary")
            return new RedBlackTree<Key, Value>();

        if (dictType == "chained_dictionary")
            return new ChainedHashTable<Key, Value>();

        if (dictType == "open_dictionary")
            return new OpenAddressingHashTable<Key, Value>();

        throw DictionaryTypeNotFound();
    }
};

#endif
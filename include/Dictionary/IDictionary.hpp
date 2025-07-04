#ifndef IDICTIONARY_HPP
#define IDICTIONARY_HPP

#include "Trees/Base/BaseTree.hpp"
#include "Visitor/IDictionaryVisitor.hpp"

/**
 * @brief Interface for a generic dictionary data structure.
 * 
 * This interface defines the basic operations for a dictionary, including
 * insertion, search, update, removal, and traversal. It also provides
 * functionality to track the number of comparisons made during operations.
 * 
 * @tparam Key The type of the keys used in the dictionary.
 * @tparam Value The type of the values stored in the dictionary.
 */
template<typename Key, typename Value>
class IDictionary {
protected:
    /**
     * @brief Tracks the number of comparisons made during dictionary operations.
     * 
     * This mutable member variable is used to count the number of comparisons
     * performed, allowing for performance analysis or debugging. Being mutable
     * allows it to be modified even in const member functions.
     */
    mutable size_t comparisonsCount = 0;

    /**
     * @brief Increments the number of comparisons by a given amount.
     * 
     * @param n The number of comparisons to add.
     */
    void incrementCounter(size_t n) const { comparisonsCount += n; }

    /**
     * @brief Resets the comparisons counter to zero.
     */
    void resetCounter() const { comparisonsCount = 0; }

public:
    /**
     * @brief Inserts a key-value pair into the dictionary.
     * 
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    virtual void insert(const Key& key, const Value& value) = 0;

    /**
     * @brief Searches for a key in the dictionary.
     * 
     * @param key The key to find.
     * @param outValue The value associated with the key, if found.
     * @return true if the key is found; false otherwise.
     */
    virtual bool find(const Key& key, Value& outValue) const = 0;

    /**
     * @brief Updates the value associated with an existing key.
     * 
     * @param key The key to update.
     * @param value The new value to associate with the key.
     */
    virtual void update(const Key& key, const Value& value) = 0;

    /**
     * @brief Removes a key and its associated value from the dictionary.
     * 
     * @param key The key to remove.
     */
    virtual void remove(const Key& key) = 0;

    /**
     * @brief Removes all entries from the dictionary.
     */
    virtual void clear() = 0;

    /**
     * @brief Prints the contents of the dictionary in order.
     * 
     * @param out The output stream to print to.
     */
    virtual void printInOrder(std::ostream& out) const = 0;

    /**
     * @brief Retrieves the number of comparisons made in the last operation.
     * 
     * @return The number of comparisons.
     */
    virtual size_t getComparisonsCount() const = 0;

    /**
     * @brief Provides access to the value associated with a key (modifiable).
     * 
     * @param key The key to access.
     * @return A reference to the value.
     */
    virtual Value& operator[](const Key& key) = 0;

    /**
     * @brief Provides access to the value associated with a key (read-only).
     * 
     * @param key The key to access.
     * @return A const reference to the value.
     */
    virtual const Value& operator[](const Key& key) const = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~IDictionary() = default;

    /**
     * @brief Accepts a visitor that performs operations on the dictionary.
     * 
     * This method allows an external visitor object to interact with the dictionary
     * by implementing the IDictionaryVisitor interface. The visitor can perform
     * custom operations on the dictionary's keys and values without exposing
     * the internal structure of the dictionary.
     * 
     * @param visitor A reference to an object implementing the IDictionaryVisitor
     * interface, which defines the operations to be performed on the dictionary.
     */
    virtual void accept(IDictionaryVisitor<Key, Value>& visitor) const = 0;
    
    template <typename Tree, typename Node, typename K, typename V>
    friend class BaseTree;

    template <typename HashTable, typename Collection, typename K, typename V, typename Hash>
    friend class BaseHashTable;
};

#endif

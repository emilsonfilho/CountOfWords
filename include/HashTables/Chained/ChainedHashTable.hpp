#ifndef CHAINED_HASH_TABLE_HPP
#define CHAINED_HASH_TABLE_HPP

#include <vector>
#include <list>
#include <utility>
#include <functional>

#include "HashTables/Base/BaseHashTable.hpp"
#include "Dictionary/IDictionary.hpp"

/**
 * @brief Hash table implementation using separate chaining.
 * 
 * @tparam Key The type of the keys.
 * @tparam Value The type of the values.
 * @tparam Hash The hash function to be used (defaults to std::hash<Key>).
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainedHashTable : public IDictionary<Key, Value>, public BaseHashTable<ChainedHashTable<Key, Value, Hash>, std::list<std::pair<Key, Value>>, Key, Value, Hash> {
    
    /**
     * @brief Result of a generic find operation within a bucket.
     * 
     * @tparam Iterator Type of the iterator used to traverse the bucket.
     * @tparam BucketRef Reference type to the bucket container.
     */
    template <typename Iterator, typename BucketRef>
    struct GenericFindResult {
        /**
         * @brief Iterator pointing to the found element or end of bucket.
         */
        Iterator iterator;

        /**
         * @brief Reference to the bucket where the element was searched.
         */
        BucketRef bucketRef;
        
        /**
         * @brief Constructs a GenericFindResult with the given iterator and bucket reference.
         * 
         * @param it Iterator pointing to the element (or end).
         * @param bRef Reference to the bucket.
         */
        GenericFindResult(Iterator it, BucketRef bRef);

        /**
         * @brief Checks whether the element was found in the bucket.
         * 
         * @return true if the iterator does not point to the end of the bucket; false otherwise.
         */
        bool wasElementFound() const;
    };

    /**
     * @brief Result type used when performing mutable find operations.
     */
    using FindResult = GenericFindResult<
        typename std::list<std::pair<Key, Value>>::iterator,
        std::list<std::pair<Key, Value>>&>;

    /**
     * @brief Result type used when performing read-only find operations.
     */
    using ConstFindResult = GenericFindResult<
        typename std::list<std::pair<Key, Value>>::const_iterator,
        const std::list<std::pair<Key, Value>>&>;

    /**
     * @brief Computes the hash code for a given key.
     * 
     * This function applies the hash function provided by the Hash template parameter
     * to the given key and ensures the result is within the bounds of the hash table
     * by taking the modulus with the table size.
     * 
     * @param key The key for which the hash code is to be computed.
     * @return size_t The computed hash code, which is the index in the hash table.
     */
    size_t hashCode(const Key& key) const;


    /**
    * @brief Finds a constant iterator to a key-value pair in the hash table.
    * 
    * This method searches for a key in the hash table and returns a constant iterator
    * to the key-value pair if found. The search is performed in the list corresponding
    * to the hash slot of the given key.
    * 
    * @param key The key to search for in the hash table.
    * 
    * @return ConstFindResult A pair consisting of a constant iterator to the found key-value
    *         pair and a reference to the list in which the key-value pair resides. If the key
    *         is not found, the iterator will be equal to the end iterator of the list.
    * 
    * @note This method increments the `comparisonsCount` member variable for each comparison
    *       made during the search.
    */
    ConstFindResult findConstPairIterator(const Key& key) const;

    /**
     * @brief Finds the iterator pointing to the pair with the specified key in the hash table.
     * 
     * This method searches for a key-value pair in the hash table and returns a result containing
     * the iterator to the found pair and a reference to the bucket (list) where the pair resides.
     * 
     * @param key The key to search for in the hash table.
     * @return FindResult A structure containing:
     *         - An iterator pointing to the found pair if the key exists, or the end iterator of the bucket if not.
     *         - A reference to the bucket (list) where the key would be located.
     */
    FindResult findPairIterator(const Key& key);
public:
    /**
     * @class ChainedHashTable
     * @brief A hash table implementation using chaining for collision resolution.
     *
     * This class provides a hash table implementation that uses separate chaining
     * to handle collisions. It supports dynamic resizing and rehashing to maintain
     * an efficient load factor.
     *
     * @param size The initial size of the hash table. Defaults to 7.
     * @param mlf The maximum load factor before rehashing occurs. Defaults to 1.0.
     */
    ChainedHashTable(size_t size = 7, float mlf = 1.0);

    /**
     * @brief Inserts a key-value pair into the hash table.
     * 
     * If the load factor exceeds the maximum load factor, the hash table will be rehashed
     * to accommodate more elements. If the key already exists in the hash table, an exception
     * of type KeyAlreadyExistsException will be thrown.
     * 
     * @param key The key to be inserted.
     * @param value The value associated with the key.
     * 
     * @throws KeyAlreadyExistsException If the key already exists in the hash table.
     */
    void insert(const Key& key, const Value& value) override;

    /**
     * @brief Searches for a key in the hash table and retrieves its associated value if found.
     * 
     * @param key The key to search for in the hash table.
     * @param outValue A reference to a variable where the associated value will be stored if the key is found.
     * @return true If the key is found in the hash table.
     * @return false If the key is not found in the hash table.
     */
    bool find(const Key& key, Value& outValue) const override;

    /**
     * @brief Updates the value associated with a given key in the hash table.
     * 
     * If the key exists in the hash table, its associated value is updated
     * to the provided value. If the key does not exist, a KeyNotFoundException
     * is thrown.
     * 
     * @param key The key whose associated value is to be updated.
     * @param value The new value to associate with the given key.
     * 
     * @throws KeyNotFoundException If the key does not exist in the hash table.
     */
    void update(const Key& key, const Value& value) override;

    /**
     * @brief Removes the key-value pair associated with the given key from the hash table.
     * 
     * If the key exists in the hash table, the corresponding key-value pair is removed.
     * If the key does not exist, no action is taken.
     * 
     * @param key The key of the key-value pair to be removed.
     * 
     * @throws None
     */
    void remove(const Key& key) override;

    /**
     * @brief Clears the hash table by removing all elements.
     * 
     * This function resets the hash table to its initial state by clearing all
     * buckets and resizing the table to its current size. The number of elements
     * in the table is also reset to zero.
     */
    void clear() override;

    /**
     * @brief Prints the key-value pairs in the hash table to the output stream in ascending order of keys.
     *
     * This function iterates through all elements in the hash table, stores them in a
     * temporary vector, sorts the vector based on the keys, and then prints each
     * key-value pair to the provided output stream. The output is formatted such that
     * keys and values are right-aligned within a field whose width is determined by
     * the maximum length of the keys and values, respectively, plus 2 for padding.
     *
     * @param out The output stream to which the key-value pairs will be printed.
     * Typically `std::cout` or a file stream.
     * @note This function requires `StringHandler::toString()` to be defined for `Key`
     * and `Value` types to correctly calculate string lengths for formatting.
     * It also assumes that the `Key` type supports the less-than operator (`<`)
     * for sorting.
     */
    void printInOrder(std::ostream& out) const override;

    /**
     * @brief Returns the current value of the comparisons count.
     *
     * This function provides access to the `comparisonsCount` attribute,
     * which is expected to track the number of key comparisons performed
     * by certain operations within the hash table (e.g., search, insertion).
     *
     * @return The current number of comparisons as a `size_t`.
     * @note Not passed to the base hash table by the function no need to add complexity to something relatively simple
     */
    size_t getComparisonsCount() const override;

    /**
     * @brief Provides read/write access to the value associated with the given key.
     *
     * If the key already exists in the hash table, this operator returns a
     * reference to the existing value, allowing it to be modified.
     * If the key does not exist, a new key-value pair is inserted into the
     * hash table with the provided key and a default-constructed value,
     * and a reference to this new value is returned.
     *
     * @param key The key whose associated value is to be accessed or inserted.
     * @return A reference to the value associated with the key.
     * @note This operator modifies the hash table if the key does not exist.
     * It assumes the existence of `findPairIterator` member function that
     * returns a `FindResult` struct/object with `wasElementFound()` and
     * `bucketRef` (a reference to the bucket list/vector) and `iterator`
     * (an iterator to the found element). It also assumes `Value` is
     * default-constructible.
     */
    Value& operator[](const Key& key) override;

    /**
     * @brief Provides read-only access to the value associated with the given key (const version).
     *
     * If the key exists in the hash table, this operator returns a constant
     * reference to the existing value. This version of the operator is used
     * when the hash table object itself is constant, preventing accidental
     * modification of its contents. If the key is not found, it throws a
     * `KeyNotFoundException`.
     *
     * @param key The key whose associated value is to be accessed.
     * @return A const reference to the value associated with the key.
     * @throws KeyNotFoundException If the key does not exist in the hash table.
     * @note This operator assumes the existence of a `findPairIterator` member
     * function (or a `const` overloaded version of it) that returns a `FindResult`
     * struct/object with `wasElementFound()` and `iterator` (an iterator to the
     * found element).
     */
    const Value& operator[](const Key& key) const override;

    /**
     * @brief Rehashes the hash table to a new size.
     * 
     * This function resizes the hash table to a new size that is the next prime 
     * number greater than or equal to the specified size `m`. It redistributes 
     * all existing key-value pairs into the new table, ensuring that the hash 
     * table maintains its integrity and performance.
     * 
     * @param m The minimum size for the new hash table. The actual size will be 
     *          the next prime number greater than or equal to `m`.
     */
    void rehash(size_t m);

    /**
     * @brief Retrieves the total number of collisions that have occurred in the hash table.
     * 
     * A collision occurs when two different keys are hashed to the same index in the hash table.
     * This method provides a count of such occurrences, which can be useful for analyzing the
     * efficiency of the hash function and the load factor of the table.
     * 
     * @return size_t The number of collisions that have occurred in the hash table.
     */
    size_t getCollissionsCount() const;

    /**
     * @brief Retrieves the current size of the hash table.
     * 
     * This function returns the total number of buckets currently allocated
     * in the hash table. It provides insight into the capacity of the table
     * and can be useful for debugging or performance analysis.
     * 
     * @return size_t The number of buckets in the hash table.
     */
    size_t getTableSize() const;

    /**
     * @brief Prints the contents of the hash table to the standard output.
     * 
     * Each slot of the hash table is printed, showing the key-value pairs
     * stored in that slot. If a slot is empty, it will display "Empty".
     * This function is primarily used for debugging and visualization
     * purposes.
     */
    void print() const;
};

#include "HashTables/Chained/ChainedHashTable.impl.hpp"

#endif


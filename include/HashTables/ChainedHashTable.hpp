#ifndef CHAINED_HASH_TABLE_HPP
#define CHAINED_HASH_TABLE_HPP

#include <vector>
#include <list>
#include <utility>
#include <functional>

#include "Dictionary/IDictionary.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainedHashTable : public IDictionary<Key, Value> {
    std::vector<std::list<std::pair<Key, Value>>> table;
    size_t tableSize;
    float maxLoadFactor;
    size_t numberOfElements;
    Hash hashing;
    int comparisonsCount;

    struct FindResult {
        typename std::list<std::pair<Key, Value>>::iterator iterator;
        std::list<std::pair<Key, Value>>& bucketRef;

        /**
         * @brief Represents the result of a search operation in a chained hash table.
         * 
         * This structure holds an iterator pointing to the found element in the bucket
         * and a reference to the bucket where the search was performed.
         * 
         * @param it An iterator pointing to the found key-value pair in the bucket.
         * @param bRef A constant reference to the bucket (a list of key-value pairs) 
         *             where the search was conducted.
         */
        FindResult(typename std::list<std::pair<Key, Value>>::iterator it, std::list<std::pair<Key, Value>>& bRef)
            : iterator(it), bucketRef(bRef) {}

        /**
         * @brief Checks if an element was found in the hash table bucket.
         * 
         * This function determines whether the iterator is not at the end of the bucket,
         * indicating that an element matching the search criteria exists in the bucket.
         * 
         * @return true if the element was found, false otherwise.
         */
        bool wasElementFound() const { return iterator != bucketRef.end(); }
    };

    /**
     * @brief Finds the next prime number greater than or equal to the given number.
     * 
     * This function calculates the smallest prime number that is greater than or 
     * equal to the input number. It uses a helper lambda function to check if a 
     * number is prime and iterates through odd numbers starting from the next 
     * candidate until a prime is found.
     * 
     * @param num The starting number to find the next prime.
     * @return size_t The next prime number greater than or equal to the input.
     */
    size_t getNextPrime(size_t num) const;

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
     * @brief Calculates and returns the current load factor of the hash table.
     * 
     * The load factor is defined as the ratio of the number of elements
     * stored in the hash table to the total number of slots (buckets) in the table.
     * 
     * @return size_t The current load factor as a floating-point value.
     */
    size_t getLoadFactor() const;

    /**
     * @brief Retrieves the maximum load factor of the hash table.
     * 
     * The maximum load factor determines the threshold at which the hash table
     * will trigger a rehash to maintain efficient operations. If the current
     * load factor (number of elements divided by table size) exceeds this value,
     * the table will resize and redistribute its elements.
     * 
     * @return The maximum load factor as a floating-point value.
     */
    size_t getMaxLoadFactor() const;

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
    bool find(const Key& key, Value& outValue) override;

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

    void printSlots(std::ostream& out) const {
        // Iterate through each bucket (slot) in the hash table's underlying storage.
        // 'table' is assumed to be a container like std::vector<std::list<...>> or similar.
        for (size_t i = 0; i < tableSize; ++i) {
            // Print the current slot number.
            out << "Slot " << i << ": ";

            // Check if the current slot is empty.
            if (table[i].empty()) {
                out << "Empty\n"; // If empty, indicate it.
            } else {
                // If not empty, iterate through all key-value pairs in this slot.
                bool firstElement = true; // Flag to handle comma separation.
                for (const auto& p : table[i]) {
                    if (!firstElement) {
                        out << ", "; // Add a comma separator for multiple elements in a slot.
                    }
                    // Print the key-value pair.
                    out << "(" << p.first << ", " << p.second << ")";
                    firstElement = false;
                }
                out << "\n"; // Newline after printing all elements in the current slot.
            }
        }
    }

};

#include "HashTables/ChainedHashTable.impl.hpp"

#endif


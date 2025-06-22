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
     * If the key already exists in the hash table, the function does nothing.
     * If the load factor exceeds the maximum load factor after the insertion,
     * the hash table is rehashed to a larger size to maintain performance.
     * 
     * @param key The key to be inserted into the hash table.
     * @param value The value associated with the key.
     */
    virtual void insert(const Key& key, const Value& value);
    virtual bool find(const Key& key, Value& outValue) {};
    virtual void update(const Key& key, const Value& value) {};
    virtual void remove(const Key& key) {};
    virtual void clear() {};
    virtual void printInOrder(std::ostream& out) const {
        for (size_t i = 0; i < tableSize; i++) {
            out << i << ": ";
            for (const auto& p : table[i]) {
                out << "(" << p.first << ", " << p.second << ") ";
            }
            out << '\n';
        }

        out << getNextPrime(39733614) << '\n'; 
    };
    virtual size_t getComparisonsCount() const {};
    virtual Value& operator[](const Key& key) {};
    virtual const Value& operator[](const Key& key) const {};
};

#include "HashTables/ChainedHashTable.impl.hpp"

#endif


#ifndef BASE_HASH_TABLE_HPP
#define BASE_HASH_TABLE_HPP

#include <vector>

template <typename HashTable, typename Collection, typename Key, typename Value, typename Hash>
class BaseHashTable {
protected:
    std::vector<Collection> table;
    size_t tableSize;
    float maxLoadFactor;
    size_t numberOfElements;
    Hash hashing;
    
    size_t getNextPrime(size_t num) const;

    void checkAndRehash();
public:
    BaseHashTable(size_t size = 7, float mlf = 0.7);

    /**
     * @brief Calculates and returns the current load factor of the hash table.
     * 
     * The load factor is defined as the ratio of the number of elements
     * stored in the hash table to the total number of slots (buckets) in the table.
     * 
     * @return size_t The current load factor as a floating-point value.
     */
    float getLoadFactor() const;

    size_t getMaxLoadFactor() const;
};

#include "HashTables/Base/BaseHashTable.impl.hpp"

#endif
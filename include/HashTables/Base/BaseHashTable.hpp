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
public:
    BaseHashTable(size_t size = 7, float mlf = 0.7);
};

#include "HashTables/Base/BaseHashTable.impl.hpp"

#endif
#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include <vector>

#include "Dictionary/IDictionary.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressingHashTable {
private:
    std::vector<std::pair<Key, Value>> table;
    size_t tableSize;
    size_t numberOfElements;
    float maxLoadFactor;
    Hash hashing;
    mutable int comparisonsCount;
};

#endif
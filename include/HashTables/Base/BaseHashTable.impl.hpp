#include "HashTables/Base/BaseHashTable.hpp"

#include <cmath>

template <typename HashTable, typename Collection, typename Key, typename Value, typename Hash>
size_t BaseHashTable<HashTable, Collection, Key, Value, Hash>::getNextPrime(size_t num) const {
    auto isPrime = [&num](size_t x) -> bool {
        if (x <= 1) return false;
        if (x == 2 or x == 3) return true;
        if (x % 2 == 0) return false;

        for (int i = 3; i <= sqrt(x); i += 2) {
            if (x % i == 0) return false;
        }

        return true;
    };
    
    size_t candidate;
    if (num % 2 == 0) candidate = num + 1;
    else candidate = num + 2;
    while (true) {
        if (isPrime(candidate)) return candidate;
        candidate += 2;
    }
}

template <typename HashTable, typename Collection, typename Key, typename Value, typename Hash>
void BaseHashTable<HashTable, Collection, Key, Value, Hash>::checkAndRehash() {
    if (getLoadFactor() >= maxLoadFactor)
        static_cast<HashTable*>(this)->rehash(2 * tableSize);
}

template <typename HashTable, typename Collection, typename Key, typename Value, typename Hash>
BaseHashTable<HashTable, Collection, Key, Value, Hash>::BaseHashTable(size_t size, float mlf) {
    tableSize = getNextPrime(size);
    table.resize(tableSize);
    maxLoadFactor = mlf <= 0 ? 0.7 : mlf;
    numberOfElements = 0;
}

template <typename HashTable, typename Collection, typename Key, typename Value, typename Hash>
float BaseHashTable<HashTable, Collection, Key, Value, Hash>::getLoadFactor() const {
    return static_cast<float>(this->numberOfElements) / this->tableSize;
}
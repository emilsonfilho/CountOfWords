#include "HashTables/ChainedHashTable.hpp"

#include <cmath>
#include "Exceptions/KeyExceptions.hpp"

template <typename Key, typename Value, typename Hash>
ChainedHashTable<Key, Value, Hash>::ChainedHashTable(size_t size, float mlf) {
    tableSize = getNextPrime(size);
    table.resize(tableSize);
    maxLoadFactor = mlf <= 0 ? 1.0 : mlf;
    numberOfElements = 0;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getNextPrime(size_t num) const {
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

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::hashCode(const Key& key) const {
    return hashing(key) % tableSize;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getLoadFactor() const {
    return static_cast<float>(numberOfElements) / tableSize;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getMaxLoadFactor() const {
    return maxLoadFactor;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::rehash(size_t m) {
    size_t newTableSize = getNextPrime(m);

    if (newTableSize > tableSize) {
        std::vector<std::list<std::pair<Key, Value>>> copy = table;
        table.clear();
        table.resize(newTableSize);
        tableSize = newTableSize;
        numberOfElements = 0;

        for (auto& line : copy) {
            for (auto& [k, v] : line)
                insert(k, v);
            line.clear();
        }
    }
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    if (getLoadFactor() >= maxLoadFactor)
        rehash(2 * tableSize);

    size_t slot = hashCode(key);
    
    for (const auto& p : table[slot])
        if (p.first == key) throw KeyAlreadyExistsException();

    table[slot].push_back({key, value});
    numberOfElements++;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::find(const Key& key, Value& outValue) {
    size_t slot = hashCode(key);

    std::list<std::pair<Key, Value>> lst = table[slot];

    auto el = std::find_if(lst.begin(), lst.end(), [&key](const std::pair<Key, Value>& p) {
        return p.first == key;
    });

    bool wasFound = el != lst.end();

    if (wasFound) outValue = el->second;
    
    return wasFound;
}
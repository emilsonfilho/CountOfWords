#include "HashTables/ChainedHashTable.hpp"

#include <cmath>
#include <iomanip>

#include "Exceptions/KeyExceptions.hpp"
#include "Utils/StringHandler.hpp"

template <typename Key, typename Value, typename Hash>
ChainedHashTable<Key, Value, Hash>::ChainedHashTable(size_t size, float mlf) {
    tableSize = getNextPrime(size);
    table.resize(tableSize);
    maxLoadFactor = mlf <= 0 ? 1.0 : mlf;
    numberOfElements = 0;
    comparisonsCount = 0;
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
typename ChainedHashTable<Key, Value, Hash>::FindResult ChainedHashTable<Key, Value, Hash>::findPairIterator(const Key& key) {
    size_t slot = hashCode(key);

    std::list<std::pair<Key, Value>>& lst = table[slot];

    auto it = std::find_if(lst.begin(), lst.end(), [this, &key](const std::pair<Key, Value>& p) {
        comparisonsCount++;
        return p.first == key;
    });

    return FindResult(it, lst);
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    if (getLoadFactor() >= maxLoadFactor)
        rehash(2 * tableSize);

    size_t slot = hashCode(key);
    
    for (const auto& p : table[slot]) {
        comparisonsCount++;
        if (p.first == key) throw KeyAlreadyExistsException();
    }

    table[slot].push_back({key, value});
    numberOfElements++;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::find(const Key& key, Value& outValue) {
    FindResult response = findPairIterator(key);

    bool wasFound = response.wasElementFound();

    if (wasFound) outValue = response.iterator->second;
    
    return wasFound;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::update(const Key& key, const Value& value) {
    FindResult response = findPairIterator(key);

    if (!response.wasElementFound()) throw KeyNotFoundException();

    response.iterator->second = value;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::remove(const Key& key) {
    FindResult response = findPairIterator(key);

    if (response.wasElementFound()) {
        response.bucketRef.erase(response.iterator);
        numberOfElements--;
    }
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::clear() {
    table.clear();
    table.resize(tableSize);
    numberOfElements = 0;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::printInOrder(std::ostream& out) const {
    size_t maxKeyLen = 0, maxValLen = 0;
    std::vector<std::pair<Key, Value>> vec;
    vec.resize(numberOfElements);

    int i = 0;
    for (const auto& line : table) {
        for (const auto& p : line) {
            maxKeyLen = std::max(maxKeyLen, StringHandler::toString(p.first).length());
            maxValLen = std::max(maxValLen, StringHandler::toString(p.second).length());

            vec[i++] = p;
        }
    }

    std::sort(vec.begin(), vec.end(), [](const auto& pa, const auto& pb) {
        return pa.first < pb.first;
    });

    for (const auto& p : vec) {
        out << std::setw(maxKeyLen + 2) << p.first << " | " << std::setw(maxValLen + 2) << p.second << "\n";
    }
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getComparisonsCount() const {
    return comparisonsCount;
}

template <typename Key, typename Value, typename Hash>
Value& ChainedHashTable<Key, Value, Hash>::operator[](const Key& key) {
    FindResult response = findPairIterator(key);

    if (!response.wasElementFound()) {
        response.bucketRef.push_back({key, Value()});
        return response.bucketRef.back().second;
    } else {
        return response.iterator->second;
    }
}

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

    size_t getNextPrime(size_t num) const;
    size_t hashCode(const Key& key) const;
    size_t getLoadFactor() const;
    size_t getMaxLoadFactor() const;
    void rehash(size_t m);
public:
    ChainedHashTable(size_t size = 7, float mlf = 1.0);

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


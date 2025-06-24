#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include <vector>

#include "Dictionary/IDictionary.hpp"
#include "HashTables/Base/BaseHashTable.hpp"
#include "HashTables/OpenAddressing/Slot.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressingHashTable : public IDictionary<Key, Value>, public BaseHashTable<OpenAddressingHashTable<Key, Value, Hash>, Slot<Key, Value>, Key, Value, Hash>{
private:
    size_t hashCode(const Key& key, size_t i) const;

    void rehash(size_t m);
public:
    OpenAddressingHashTable(size_t size = 8, float mlf = 0.7);

    void insert(const Key& key, const Value& value);
    bool find(const Key& key, Value& outValue) { return false; };
    void update(const Key& key, const Value& value) {};
    void remove(const Key& key) {};
    void clear() {};
    void printInOrder(std::ostream& out) const {
        for (const auto& slot : this->table) {
            out << "(" << slot.key << ", " << slot.value << ")\n";
        }
    };
    size_t getComparisonsCount() const { return 0; };
    Value& operator[](const Key& key) {};
    const Value& operator[](const Key& key) const {};

    template <typename HashTable, typename Collection, typename K, typename V, typename H>
    friend class BaseHashTable;
};

#include "HashTables/OpenAddressing/OpenAddressingHashTable.impl.hpp"

#endif
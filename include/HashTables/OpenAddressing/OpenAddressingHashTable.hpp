#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include <vector>

#include "Dictionary/IDictionary.hpp"
#include "HashTables/Base/BaseHashTable.hpp"
#include "HashTables/OpenAddressing/Slot.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressingHashTable : public IDictionary<Key, Value>, public BaseHashTable<OpenAddressingHashTable<Key, Value, Hash>, Slot<Key, Value>, Key, Value, Hash>{
private:
    template <typename Entry>
    struct GenericFindResult {
        Entry* slot;

        GenericFindResult(Entry* e)
            : slot(e) {}

        bool wasElementFound() const { return slot != nullptr; }
    };

    using FindResult = GenericFindResult<Slot<Key, Value>>;
    using ConstFindResult = GenericFindResult<const Slot<Key, Value>>;

    size_t hashCode(const Key& key, size_t i) const;

    void rehash(size_t m);

    ConstFindResult findConstSlot(const Key& key) {
        const Slot<Key, Value>* tableSlot = nullptr;
        
        for (size_t i = 0; i < this->tableSize; i++) {
            size_t slotIdx = hashCode(key, i);
            const Slot<Key, Value>& slot = this->table[slotIdx];

            this->comparisonsCount++;

            if (slot.status == EMPTY)
                break;

            if (slot.status == ACTIVE and slot.key == key)
                tableSlot = &slot;
        }

        return ConstFindResult(tableSlot);
    }

    FindResult findSlot(const Key& key) {
        Slot<Key, Value>* tableSlot = nullptr;
        
        for (size_t i = 0; i < this->tableSize; i++) {
            size_t slotIdx = hashCode(key, i);
            Slot<Key, Value>& slot = this->table[slotIdx];

            this->comparisonsCount++;

            if (slot.status == EMPTY)
                break;

            if (slot.status == ACTIVE and slot.key == key)
                tableSlot = &slot;
        }

        return FindResult(tableSlot);
    }
public:
    OpenAddressingHashTable(size_t size = 8, float mlf = 0.7);

    void insert(const Key& key, const Value& value);
    bool find(const Key& key, Value& outValue);
    void update(const Key& key, const Value& value);
    void remove(const Key& key);
    void clear();
    void printInOrder(std::ostream& out) const;
    size_t getComparisonsCount() const;
    Value& operator[](const Key& key) {};
    const Value& operator[](const Key& key) const {};

    template <typename HashTable, typename Collection, typename K, typename V, typename H>
    friend class BaseHashTable;
};

#include "HashTables/OpenAddressing/OpenAddressingHashTable.impl.hpp"

#endif
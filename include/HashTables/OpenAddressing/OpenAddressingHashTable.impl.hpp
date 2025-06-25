#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <iostream>

#include "Exceptions/KeyExceptions.hpp"

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::hashCode(const Key& key, size_t i) const {
    return (this->hashing(key) + (i + i * i) / 2) % this->tableSize;
}

template <typename Key, typename Value, typename Hash>
OpenAddressingHashTable<Key, Value, Hash>::OpenAddressingHashTable(size_t size, float mlf)
    : BaseHashTable<OpenAddressingHashTable<Key, Value, Hash>, Slot<Key, Value>, Key, Value, Hash>(size, mlf) {}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::rehash(size_t m) {

    if (m > this->tableSize) {
        std::vector<Slot<Key, Value>> copy = this->table;
        this->table.clear();
        this->table.resize(m);
        this->tableSize = m;
        this->numberOfElements = 0;

        for (auto& slot : copy) {
            if (slot.status == ACTIVE)
                insert(slot.key, slot.value);
        }
    }
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    this->checkAndRehash();
    
    int lastDeletedSlot = -1;

    for (int i = 0; i < this->tableSize; i++) {
        size_t slotIdx = hashCode(key, i);
        Slot<Key, Value>& slot = this->table[slotIdx];


        if (slot.status == EMPTY) {
            slot = Slot(key, value);
            this->numberOfElements++;
            return;
        } else if (slot.status == ACTIVE and slot.key == key) {
            throw KeyAlreadyExistsException();
        } else if (slot.status == DELETED and lastDeletedSlot == -1) {
            lastDeletedSlot = slotIdx;
        }
    }

    if (lastDeletedSlot == -1) {
        throw std::runtime_error("tabela cheia");
    } else {
        this->table[lastDeletedSlot] = Slot(key, value);
    }
}
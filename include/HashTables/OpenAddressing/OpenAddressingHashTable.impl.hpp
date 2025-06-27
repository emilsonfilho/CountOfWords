#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <iostream>
#include <algorithm>

#include "Exceptions/KeyExceptions.hpp"

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::hashCode(const Key& key, size_t i) const {
    return (this->hashing(key) + ((i + (i * i)) / 2)) % this->tableSize;
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
            this->incrementCounter(1);
            slot = Slot(key, value);
            this->numberOfElements++;
            return;
        } else if (slot.status == ACTIVE and slot.key == key) {
            this->incrementCounter(2);
            throw KeyAlreadyExistsException();
        } else if (slot.status == DELETED and lastDeletedSlot == -1) {
            this->incrementCounter(3);
            lastDeletedSlot = slotIdx;
        } else {
            this->incrementCounter(3);
        }
    }

    this->table[lastDeletedSlot] = Slot(key, value);
}

template <typename Key, typename Value, typename Hash>
bool OpenAddressingHashTable<Key, Value, Hash>::find(const Key& key, Value& outValue) {
    ConstFindResult response = findConstSlot(key);
    bool wasElementFound = response.wasElementFound();

    if (wasElementFound)
        outValue = response.slot->value;

    return wasElementFound;
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::update(const Key& key, const Value& value) {
    FindResult response = findSlot(key);
    bool wasElementFound = response.wasElementFound();

    if (!wasElementFound)
        throw KeyNotFoundException();

    response.slot->value = value;
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::remove(const Key& key) {
    FindResult response = findSlot(key);
    
    if (response.wasElementFound())
        response.slot->status = DELETED;
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::clear() {
    this->clearHashTable();
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::printInOrder(std::ostream& out) const {
    size_t maxKeyLen = 0, maxValLen = 0, i = 0;
    std::vector<Slot<Key, Value>> vec(this->numberOfElements);

    for (const Slot<Key, Value>& slot : this->table) {
        if (slot.status == ACTIVE) {
            maxKeyLen = std::max(maxKeyLen, StringHandler::size(slot.key));
            maxValLen = std::max(maxValLen, StringHandler::size(slot.value));
            
            vec[i++] = slot;
        }
    }

    std::sort(vec.begin(), vec.end(), [](const Slot<Key, Value>& slotA, const Slot<Key, Value>& slotB) {
        return slotA.key < slotB.key;
    });

    for (const Slot<Key, Value>& slot : vec)
        if (slot.status == ACTIVE)
            out << StringHandler::SetWidthAtLeft(slot.key, maxKeyLen) << " | " << StringHandler::SetWidthAtLeft(slot.value, maxValLen) << "\n";
}

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::getComparisonsCount() const {
    return this->comparisonsCount;
}

template <typename Key, typename Value, typename Hash>
Value& OpenAddressingHashTable<Key, Value, Hash>::operator[](const Key& key) {
    this->checkAndRehash();

    FindResult response = findSlot(key);

    if (response.wasElementFound())
        return response.slot->value;

    this->numberOfElements++;
    response.availableSlot->key = key;
    response.availableSlot->value = Value();
    response.availableSlot->status = ACTIVE;
    return response.availableSlot->value;
}

template <typename Key, typename Value, typename Hash>
const Value& OpenAddressingHashTable<Key, Value, Hash>::operator[](const Key& key) const {
    ConstFindResult response = findConstSlot(key);

    if (!response.wasElementFound())
        throw KeyNotFoundException();

    return response.slot->value;
}
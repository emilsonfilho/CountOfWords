#include "HashTables/OpenAddressing/OpenAddressingHashTable.hpp"

#include <iostream>
#include <algorithm>

#include "Exceptions/KeyExceptions.hpp"

template <typename Key, typename Value, typename Hash>
template <typename Entry>
OpenAddressingHashTable<Key, Value, Hash>::GenericFindResult<Entry>::GenericFindResult(Entry* e, Entry* as)
    : slot(e), availableSlot(as) {}

template <typename Key, typename Value, typename Hash>
template <typename Entry>
bool OpenAddressingHashTable<Key, Value, Hash>::GenericFindResult<Entry>::wasElementFound() const {
    return slot != nullptr;
}

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::hashCode(const Key& key, size_t i) const {
    return (this->hashing(key) + ((i + (i * i)) / 2)) % this->tableSize;
}

template <typename Key, typename Value, typename Hash>
typename OpenAddressingHashTable<Key, Value, Hash>::ConstFindResult OpenAddressingHashTable<Key, Value, Hash>::findConstSlot(const Key& key) const {
    const Slot<Key, Value>* tableSlot = nullptr;
        
    for (size_t i = 0; i < this->tableSize; i++) {
        size_t slotIdx = hashCode(key, i);

        const Slot<Key, Value>& slot = this->table[slotIdx];

        if (slot.status == EMPTY) {
            this->incrementCounter(1);
            break;
        }

        if (slot.status == ACTIVE and slot.key == key)
            tableSlot = &slot;
        
        this->incrementCounter(2);
    }

    return ConstFindResult(tableSlot);
}

template <typename Key, typename Value, typename Hash>
typename OpenAddressingHashTable<Key, Value, Hash>::FindResult OpenAddressingHashTable<Key, Value, Hash>::findSlot(const Key& key) {
    Slot<Key, Value> *tableSlot = nullptr, *availableSlot = nullptr;

    for (size_t i = 0; i < this->tableSize; i++) {
        size_t slotIdx = hashCode(key, i);
        Slot<Key, Value>& slot = this->table[slotIdx];

        if (slot.status == EMPTY) {
            if (!availableSlot)
                availableSlot = &slot;

            this->incrementCounter(2);

            break;
        }

        if (slot.status == ACTIVE and slot.key == key) {
            this->incrementCounter(2);

            tableSlot = &slot;
            break;
        }

        if (slot.status == DELETED and !availableSlot)
            availableSlot = &slot;

        this->incrementCounter(3);

    }

    return FindResult(tableSlot, availableSlot);
}

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::nextBase2Of(size_t m) const {
    if (m <= 0)
        return 1;
    
    

    size_t n = m, bits = sizeof(size_t) * 8;

    for (size_t i = 1; i < bits; i *= 2)
        n |= n >> i;

    return (n + 1);
}

template <typename Key, typename Value, typename Hash>
OpenAddressingHashTable<Key, Value, Hash>::OpenAddressingHashTable(size_t size, float mlf)
    : BaseHashTable<OpenAddressingHashTable<Key, Value, Hash>, Slot<Key, Value>, Key, Value, Hash>(nextBase2Of(size), mlf) {}

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
            if (lastDeletedSlot == -1) {
                this->incrementCounter(1);
                slot = Slot(key, value);
                this->numberOfElements++;
                return;
            }

            break;
        } else if (slot.status == ACTIVE and slot.key == key) {
            this->incrementCounter(2);
            throw KeyAlreadyExistsException();
        } else if (slot.status == ACTIVE and slot.key != key) {
            this->incrementCollisionsCount();
            this->incrementCounter(3);
        } else if (slot.status == DELETED and lastDeletedSlot == -1) {
            this->incrementCounter(4);
            lastDeletedSlot = slotIdx;
        } else {
            this->incrementCounter(4);
        }
    }

    this->table[lastDeletedSlot] = Slot(key, value);
}

template <typename Key, typename Value, typename Hash>
bool OpenAddressingHashTable<Key, Value, Hash>::find(const Key& key, Value& outValue) const {
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

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::getCollisionsCount() const {
    return this->collisionsCount;
}

template <typename Key, typename Value, typename Hash>
size_t OpenAddressingHashTable<Key, Value, Hash>::getTableSize() const {
    return this->tableSize;
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::print() const {
    for (size_t i = 0; i < this->table.size(); ++i) {
        const auto& slot = this->table[i];
        std::cout << "Slot " << i << ": ";
        if (slot.status == EMPTY) {
            std::cout << "EMPTY";
        } else if (slot.status == DELETED) {
            std::cout << "DELETED";
        } else if (slot.status == ACTIVE) {
            std::cout << "ACTIVE [" << slot.key << ": " << slot.value << "]";
        }
        std::cout << '\n';
    }
}

template <typename Key, typename Value, typename Hash>
void OpenAddressingHashTable<Key, Value, Hash>::accept(IDictionaryVisitor<Key, Value>& visitor) {
	visitor.collectMetrics(*this);
}
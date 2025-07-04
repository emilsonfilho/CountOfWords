#include "HashTables/Chained/ChainedHashTable.hpp"

#include <cmath>
#include <iomanip>

#include "Exceptions/KeyExceptions.hpp"
#include "Utils/Strings/StringHandler.hpp"

template <typename Key, typename Value, typename Hash>
template <typename Iterator, typename BucketRef>
ChainedHashTable<Key, Value, Hash>::GenericFindResult<Iterator, BucketRef>::GenericFindResult(
    Iterator it, BucketRef bRef)
    : iterator(it), bucketRef(bRef) {}

template <typename Key, typename Value, typename Hash>
template <typename Iterator, typename BucketRef>
bool ChainedHashTable<Key, Value, Hash>::GenericFindResult<Iterator, BucketRef>::wasElementFound() const {
    return iterator != bucketRef.end();
}

template <typename Key, typename Value, typename Hash>
ChainedHashTable<Key, Value, Hash>::ChainedHashTable(size_t size, float mlf)
    : BaseHashTable<ChainedHashTable<Key, Value, Hash>, std::list<std::pair<Key, Value>>, Key, Value, Hash>(this->getNextPrime(size), mlf) {}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::hashCode(const Key& key) const {
    return this->hashing(key) % this->tableSize;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::rehash(size_t m) {
    size_t newTableSize = this->getNextPrime(m);

    if (newTableSize > this->tableSize) {
        std::vector<std::list<std::pair<Key, Value>>> copy = this->table;
        this->table.clear();
        this->table.resize(newTableSize);
        this->tableSize = newTableSize;
        this->numberOfElements = 0;

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

   

    std::list<std::pair<Key, Value>>& lst = this->table[slot];

    auto it = std::find_if(lst.begin(), lst.end(), [this, &key](const std::pair<Key, Value>& p) {
        this->comparisonsCount++;
        return p.first == key;
    });

    return FindResult(it, lst);
}

template <typename Key, typename Value, typename Hash>
typename ChainedHashTable<Key, Value, Hash>::ConstFindResult ChainedHashTable<Key, Value, Hash>::findConstPairIterator(const Key& key) const {
    size_t slot = hashCode(key);

   

    const std::list<std::pair<Key, Value>>& lst = this->table[slot];

    auto it = std::find_if(lst.begin(), lst.end(), [this, &key](const std::pair<Key, Value>& p) {
        this->comparisonsCount++;
        return p.first == key;
    });

    return ConstFindResult(it, lst);
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    this->checkAndRehash();

    size_t slot = hashCode(key);
   
    if (!this->table[slot].empty())
        this->incrementCollisionsCount();

    for (const auto& p : this->table[slot]) {
        this->comparisonsCount++;
        if (p.first == key) throw KeyAlreadyExistsException();
    }

    this->table[slot].push_back({key, value});
    this->numberOfElements++;
}

template <typename Key, typename Value, typename Hash>
bool ChainedHashTable<Key, Value, Hash>::find(const Key& key, Value& outValue) const {
    ConstFindResult response = findConstPairIterator(key);

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
        this->numberOfElements--;
    }
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::clear() {
    this->clearHashTable();
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::printInOrder(std::ostream& out) const {
    size_t maxKeyLen = 0, maxValLen = 0;
    std::vector<std::pair<Key, Value>> vec(this->numberOfElements);

    size_t i = 0;
    for (const auto& line : this->table) {
        for (const auto& p : line) {
            maxKeyLen = std::max(maxKeyLen, StringHandler::size(p.first));
            maxValLen = std::max(maxValLen, StringHandler::size(p.second));

            vec[i++] = p;
        }
    }

    std::sort(vec.begin(), vec.end(), [](const auto& pa, const auto& pb) {
        return pa.first < pb.first;
    });


    for (const auto& p : vec) {
        out << StringHandler::SetWidthAtLeft(p.first, maxKeyLen) << " | " << StringHandler::SetWidthAtLeft(p.second, maxValLen) << "\n";
    }
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getComparisonsCount() const {
    return this->comparisonsCount;
}

template <typename Key, typename Value, typename Hash>
Value& ChainedHashTable<Key, Value, Hash>::operator[](const Key& key) {
    this->checkAndRehash();

    FindResult response = findPairIterator(key);

    if (!response.wasElementFound()) {

        response.bucketRef.push_back({key, Value()});
        this->numberOfElements++;
        return response.bucketRef.back().second;
    } else {
        return response.iterator->second;
    }
}

template <typename Key, typename Value, typename Hash>
const Value& ChainedHashTable<Key, Value, Hash>::operator[](const Key& key) const {
    ConstFindResult response = findConstPairIterator(key);

    if (!response.wasElementFound()) {
        throw KeyNotFoundException();
    } else {
        return response.iterator->second;
    }
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getCollisionsCount() const {
    return this->collisionsCount;
}

template <typename Key, typename Value, typename Hash>
size_t ChainedHashTable<Key, Value, Hash>::getTableSize() const {
    return this->tableSize;
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::print() const {
    for (size_t i = 0; i < this->table.size(); ++i) {
        std::cout << "Slot " << i << ": ";
        if (this->table[i].empty()) {
        std::cout << "Empty";
        } else {
        for (const auto& pair : this->table[i]) {
            std::cout << "[" << pair.first << ": " << pair.second << "] ";
        }
        }
        std::cout << "\n";
    }
}

template <typename Key, typename Value, typename Hash>
void ChainedHashTable<Key, Value, Hash>::accept(IDictionaryVisitor<Key, Value>& visitor) const {
	visitor.collectMetrics(*this);
}
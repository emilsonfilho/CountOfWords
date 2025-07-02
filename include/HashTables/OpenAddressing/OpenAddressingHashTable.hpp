#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include <vector>

#include "Dictionary/IDictionary.hpp"
#include "HashTables/Base/BaseHashTable.hpp"
#include "HashTables/OpenAddressing/Slot.hpp"

/**
 * @brief Hash table implementation using open addressing.
 * 
 * @tparam Key The type of the keys.
 * @tparam Value The type of the values.
 * @tparam Hash The hash function to be used (defaults to std::hash<Key>).
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressingHashTable : public IDictionary<Key, Value>, public BaseHashTable<OpenAddressingHashTable<Key, Value, Hash>, Slot<Key, Value>, Key, Value, Hash>{
private:
    /**
     * @brief Result of a probing operation in open addressing.
     * 
     * @tparam Entry Type of the slot being probed.
     */
    template <typename Entry>
    struct GenericFindResult {
        /**
         * @brief Pointer to the slot where the key was found (or where the search ended).
         */
        Entry* slot;

        /**
         * @brief Pointer to the first available (empty or deleted) slot encountered during probing.
         */
        Entry* availableSlot;

        /**
         * @brief Constructs a GenericFindResult with the given slot and optional available slot.
         * 
         * @param e Pointer to the slot where the key was found (or search ended).
         * @param as Pointer to the first available slot (optional, may be nullptr).
         */
        GenericFindResult(Entry* e, Entry* as = nullptr);

        /**
         * @brief Checks whether the element was found in the table.
         * 
         * @return true if the slot pointer is not null and refers to a valid element.
         */
        bool wasElementFound() const;
    };

    /**
     * @brief Result type used when performing mutable find operations.
     */
    using FindResult = GenericFindResult<Slot<Key, Value>>;

    /**
     * @brief Result type used when performing read-only find operations.
     */
    using ConstFindResult = GenericFindResult<const Slot<Key, Value>>;


    /**
     * @brief Computes the hash code for a given key and probe number.
     *
     * This function generates a hash code using a combination of the primary hash
     * function and quadratic probing. The quadratic probing formula ensures that
     * collisions are resolved by probing different slots in the hash table.
     *
     * @param key The key for which the hash code is to be computed.
     * @param i The probe number, used to calculate the offset for quadratic probing.
     * @return The computed hash code, which is the index in the hash table.
     */
    size_t hashCode(const Key& key, size_t i) const;

    /**
     * @brief Searches for a constant slot in the hash table that matches the given key.
     * 
     * This method performs a search for the specified key in the hash table using the 
     * open addressing technique. It returns a result containing a pointer to the slot 
     * if the key is found, or a null pointer if the key is not present in the table.
     * 
     * @param key The key to search for in the hash table.
     * @return ConstFindResult A result object containing a pointer to the slot if found, 
     *         or a null pointer if the key is not present.
     */
    ConstFindResult findConstSlot(const Key& key) const;

    /**
     * @brief Finds a slot in the hash table for the given key.
     * 
     * This method searches for a slot in the hash table that corresponds to the specified key.
     * It returns a FindResult object containing pointers to the slot where the key is found (if it exists)
     * and the first available slot (if any). The search uses open addressing with quadratic probing.
     * 
     * @param key The key to search for in the hash table.
     * @return FindResult A structure containing:
     *         - A pointer to the slot where the key is found (if it exists), or nullptr otherwise.
     *         - A pointer to the first available slot (if any), or nullptr if no available slot is found.
     */
    FindResult findSlot(const Key& key);

    /**
     * @brief Calculates the next power of 2 greater than or equal to the given number.
     * 
     * This function determines the smallest power of 2 that is greater than or equal to the input value `m`.
     * It is useful for ensuring that certain data structures, such as hash tables, have sizes that are powers of 2,
     * which can optimize certain operations like hashing.
     * 
     * @param m The input number for which the next power of 2 is to be calculated.
     * @return The smallest power of 2 greater than or equal to `m`.
     */
    size_t nextBase2Of(size_t m) const;
public:
    /**
     * @brief Constructs an OpenAddressingHashTable with a specified initial size and maximum load factor.
     * 
     * @param size The initial size of the hash table. Defaults to 8 if not specified.
     * @param mlf The maximum load factor (a value between 0 and 1) that determines when the table should be rehashed. Defaults to 0.7 if not specified.
     */
    OpenAddressingHashTable(size_t size = 8, float mlf = 0.7);

    /**
     * @brief Inserts a key-value pair into the hash table.
     * 
     * This function attempts to insert the given key and value into the hash table.
     * If the key already exists in the table, a KeyAlreadyExistsException is thrown.
     * If the table is full or requires rehashing, the function will handle rehashing
     * before proceeding with the insertion.
     * 
     * @param key The key to be inserted into the hash table.
     * @param value The value associated with the key to be inserted.
     * 
     * @throws KeyAlreadyExistsException If the key already exists in the hash table.
     */
    void insert(const Key& key, const Value& value);

    /**
     * @brief Searches for a key in the hash table and retrieves its associated value if found.
     * 
     * @param key The key to search for in the hash table.
     * @param outValue A reference to a variable where the value associated with the key will be stored if found.
     * @return true If the key is found in the hash table.
     * @return false If the key is not found in the hash table.
     * 
     * @throws None
     */
    bool find(const Key& key, Value& outValue) const;

    /**
     * @brief Updates the value associated with the given key in the hash table.
     * 
     * If the key exists in the hash table, its associated value is updated to the provided value.
     * If the key does not exist, a KeyNotFoundException is thrown.
     * 
     * @param key The key whose associated value is to be updated.
     * @param value The new value to associate with the given key.
     * 
     * @throws KeyNotFoundException If the key is not found in the hash table.
     */
    void update(const Key& key, const Value& value);

    /**
     * @brief Removes the element associated with the given key from the hash table.
     * 
     * If the key is found in the hash table, the corresponding slot's status is marked as DELETED.
     * If the key is not found, the function does nothing.
     * 
     * @param key The key of the element to be removed.
     */
    void remove(const Key& key);
    
    /**
     * @brief Clears the hash table by removing all elements and resetting its state.
     * 
     * This function removes all active elements from the hash table and resets
     * the internal data structure to its initial state. After calling this function,
     * the hash table will be empty, and all slots will be marked as empty.
     */
    void clear();
    
    /**
     * @brief Prints the contents of the hash table in order of keys.
     * 
     * This function iterates through all active slots in the hash table,
     * collects them into a vector, and sorts them by their keys. It then
     * outputs the key-value pairs in a formatted manner to the provided
     * output stream.
     * 
     * @param out The output stream where the formatted key-value pairs
     *            will be printed.
     */
    void printInOrder(std::ostream& out) const;

    /**
     * @brief Retrieves the total number of comparisons made during hash table operations.
     * 
     * This method returns the count of comparisons performed while searching for,
     * inserting, or updating elements in the hash table. It is useful for analyzing
     * the efficiency of the hash table operations.
     * 
     * @return size_t The number of comparisons made.
     */
    size_t getComparisonsCount() const;

    /**
     * @brief Accesses or inserts a value associated with the given key.
     * 
     * If the key exists in the hash table, this operator returns a reference to the associated value.
     * If the key does not exist, a new entry is created with the given key and a default-constructed
     * value, and a reference to the newly created value is returned.
     * 
     * @param key The key to search for or insert into the hash table.
     * @return Value& A reference to the value associated with the given key.
     * 
     * @note This function may trigger a rehash if the load factor exceeds the maximum load factor.
     * @throws std::bad_alloc If memory allocation fails during rehashing or insertion.
     */
    Value& operator[](const Key& key);

    /**
     * @brief Accesses the value associated with the given key in the hash table.
     * 
     * This operator provides read-only access to the value corresponding to the specified key.
     * If the key is not found in the hash table, a KeyNotFoundException is thrown.
     * 
     * @param key The key whose associated value is to be accessed.
     * @return const Value& A constant reference to the value associated with the key.
     * @throws KeyNotFoundException If the key is not found in the hash table.
     */
    const Value& operator[](const Key& key) const;

    /**
     * @brief Resizes the hash table to a new size and rehashes all existing elements.
     * 
     * This function increases the size of the hash table to the specified value `m` 
     * (if `m` is greater than the current table size) and rehashes all active elements 
     * into the new table. The rehashing process ensures that the hash table maintains 
     * its integrity and performance after resizing.
     * 
     * @param m The new size of the hash table. Must be greater than the current table size.
     */
    void rehash(size_t m);

    /**
     * @brief Retrieves the total number of collisions that have occurred in the hash table.
     * 
     * A collision occurs when two different keys are hashed to the same index in the table.
     * This function provides a count of such collisions, which can be useful for analyzing
     * the efficiency of the hash function and the overall performance of the hash table.
     * 
     * @return size_t The number of collisions that have occurred.
     */
    size_t getCollisionsCount() const;

    /**
     * @brief Retrieves the size of the hash table.
     * 
     * This function returns the total number of slots available in the hash table,
     * which represents its capacity. It does not indicate the number of elements
     * currently stored in the table.
     * 
     * @return size_t The total number of slots in the hash table.
     */
    size_t getTableSize() const;

    /**
     * @brief Prints all slots in the hash table, including empty and deleted ones.
     * 
     * This function iterates through all slots in the hash table and prints their
     * status (EMPTY, DELETED, or OCCUPIED) along with their key-value pairs if applicable.
     * 
     * @param out The output stream where the slot information will be printed.
     */
    void print() const;
};

#include "HashTables/OpenAddressing/OpenAddressingHashTable.impl.hpp"

#endif
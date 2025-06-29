#ifndef BASE_HASH_TABLE_HPP
#define BASE_HASH_TABLE_HPP

#include <vector>

template <typename HashTable, typename Collection, typename Key, typename Value, typename Hash>
class BaseHashTable {
protected:
    std::vector<Collection> table;
    size_t tableSize;
    float maxLoadFactor;
    size_t numberOfElements;
    Hash hashing;
    mutable size_t collisionsCount;
    
    /**
     * @brief Calculates and returns the next prime number greater than or equal to a given number.
     *
     * This method finds the smallest prime number that is greater than or equal to
     * the input `num`. It uses a lambda function `isPrime` to efficiently check
     * for primality. The search starts from `num` (or `num + 1` if `num` is even)
     * and increments by 2 to only check odd numbers, optimizing the search.
     *
     * @param num The starting number from which to find the next prime.
     * @return The next prime number greater than or equal to `num`.
     */
    size_t getNextPrime(size_t num) const;

    /**
     * @brief Checks the current load factor and triggers a rehash if necessary.
     *
     * This method is responsible for maintaining the efficiency of the hash table.
     * It compares the current load factor (the ratio of elements to table size)
     * against a predefined maximum load factor (`maxLoadFactor`). If the current
     * load factor exceeds this maximum, it indicates that the hash table is becoming
     * too dense, potentially leading to increased collision rates and slower operations.
     *
     * In such a scenario, the method initiates a rehash operation by calling the
     * `rehash` method of the derived `HashTable` class (using CRTP) with a new
     * table size that is double the current `tableSize`. This effectively resizes
     * the hash table and redistributes existing elements, improving performance.
     */
    void checkAndRehash();
public:
    /**
     * @brief Constructs a new BaseHashTable object.
     *
     * Initializes a new hash table with a specified initial size and maximum load factor.
     * The actual size of the hash table is set to the next prime number greater than
     * or equal to the provided `size` to optimize hash distribution. The `table`
     * (likely a vector of `Collection`s) is then resized accordingly.
     *
     * The `maxLoadFactor` is set based on the `mlf` parameter. If `mlf` is less than
     * or equal to 0, it defaults to 0.7 to ensure a reasonable threshold for rehashing.
     * The `numberOfElements` is initialized to 0, as the table is empty upon construction.
     *
     * @param size The desired initial size of the hash table. This will be adjusted to the next prime.
     * @param mlf The maximum load factor for the hash table. If the load factor exceeds this value, a rehash operation will be triggered.
     */
    BaseHashTable(size_t size = 7, float mlf = 0.7);

    /**
     * @brief Calculates and returns the current load factor of the hash table.
     * 
     * The load factor is defined as the ratio of the number of elements
     * stored in the hash table to the total number of slots (buckets) in the table.
     * 
     * @return size_t The current load factor as a floating-point value.
     */
    float getLoadFactor() const;

    /**
     * @brief Clears all elements from the hash table, resetting it to an empty state.
     *
     * This method effectively empties the hash table while retaining its current capacity.
     * It first clears all elements from the underlying `table` (which likely holds the
     * collections for each bucket). After clearing, it resizes the `table` back to its
     * original `tableSize`, ensuring that the structure remains intact but empty.
     * Finally, `numberOfElements` is reset to 0, accurately reflecting the empty state.
     */
    void clearHashTable();

    void incrementCollisionsCount(size_t m = 1) const;
};

#include "HashTables/Base/BaseHashTable.impl.hpp"

#endif
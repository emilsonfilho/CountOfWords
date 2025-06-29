#ifndef SLOT_HPP
#define SLOT_HPP

enum Status { EMPTY, ACTIVE, DELETED };

template <typename Key, typename Value>
/**
 * @struct Slot
 * @brief Represents a slot in an open addressing hash table.
 *
 * The Slot structure is used to store a key-value pair along with its status
 * in an open addressing hash table. The status indicates whether the slot
 * is empty, active, or deleted.
 *
 * @var Slot::key
 * The key associated with the slot.
 *
 * @var Slot::value
 * The value associated with the slot.
 *
 * @var Slot::status
 * The status of the slot, which can be EMPTY, ACTIVE, or DELETED.
 *
 * @fn Slot::Slot()
 * Default constructor that initializes the slot with an EMPTY status.
 *
 * @fn Slot::Slot(const Key& k, const Value& v)
 * Parameterized constructor that initializes the slot with a given key and value,
 * and sets the status to ACTIVE.
 *
 * @note The `Key` and `Value` types, as well as the `Status` enumeration, are assumed
 * to be defined elsewhere in the codebase.
 */
struct Slot {
        /**
     * @brief The key associated with this slot.
     */
    Key key;

    /**
     * @brief The value associated with the key.
     */
    Value value;

    /**
     * @brief The current status of the slot (e.g., EMPTY, ACTIVE, DELETED).
     */
    Status status;

    /**
     * @brief Default constructor. Initializes the slot as EMPTY.
     */
    Slot(): status(EMPTY) {}

    /**
     * @brief Constructs a slot with a key and value. Sets status to ACTIVE.
     * 
     * @param k The key to store.
     * @param v The value associated with the key.
     */
    Slot(const Key& k, const Value& v): key(k), value(v), status(ACTIVE) {}

};

#endif
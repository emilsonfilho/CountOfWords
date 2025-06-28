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
    Key key;
    Value value;
    Status status;

    Slot(): status(EMPTY) {}

    Slot(const Key& k, const Value& v): key(k), value(v), status(ACTIVE) {}
};

#endif
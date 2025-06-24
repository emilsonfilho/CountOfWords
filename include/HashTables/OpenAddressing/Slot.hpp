#ifndef SLOT_HPP
#define SLOT_HPP

enum Status { EMPTY, ACTIVE, DELETED };

template <typename Key, typename Value>
struct Slot {
    Key key;
    Value value;
    Status status;

    Slot(): status(EMPTY) {}

    Slot(const Key& k, const Value& v): key(k), value(v), status(ACTIVE) {}
};

#endif
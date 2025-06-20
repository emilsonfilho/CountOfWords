#ifndef INODE_HPP
#define INODE_HPP

#include <utility>
#include <sstream>

template <typename Key, typename Value>
class Node {
    std::pair<Key, Value> data;
public:
    Node(const Key& key, const Value& value): data({key, value}) {}

    const Key& getKey() const { return data.first; }
    void setKey(const Key& key) { data.first = key; }

    const Value& getValue() const { return data.second; }
    Value& getValue() { return data.second; }
    void setValue(const Value& value) { data.second = value; }

    void update(const Key& key, const Value& value) {
        setKey(key);
        setValue(value);
    }

    std::string show() const {
        std::ostringstream os;
		os << "(" << getKey() << ", " << getValue() << ")";
		return os.str();
    }

    ~Node() = default;
};

#endif

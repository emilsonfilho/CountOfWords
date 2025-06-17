#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

template<typename Key, typename Value>
class Dictionary {
public:
    virtual void insert(const Key& key, const Value& value) = 0;
    virtual bool find(const Key& key, Value& outValue) = 0;
    virtual void update(const Key& key, const Value& value) = 0;
    virtual void remove(const Key& key) = 0;
    virtual void clear() = 0;
    virtual void printInOrder(std::ostream& out) = 0;
    virtual size_t getComparisonsCount() const = 0;
    virtual ~Dictionary() = default;
};

#endif
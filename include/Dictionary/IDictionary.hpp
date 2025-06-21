#ifndef IDICTIONARY_HPP
#define IDICTIONARY_HPP

#include "Trees/Base/BaseTree.hpp"

template<typename Key, typename Value>
class IDictionary {
protected:
    mutable size_t comparisonsCount = 0;

    void incrementCounter() const { comparisonsCount++; }
public:
    virtual void insert(const Key& key, const Value& value) = 0;
    virtual bool find(const Key& key, Value& outValue) = 0;
    virtual void update(const Key& key, const Value& value) = 0;
    virtual void remove(const Key& key) = 0;
    virtual void clear() = 0;
    virtual void printInOrder(std::ostream& out) const = 0;
    virtual size_t getComparisonsCount() const = 0;
    virtual Value& operator[](const Key& key) = 0;
    virtual const Value& operator[](const Key& key) const = 0;
    virtual ~IDictionary() = default;
    
    template <typename Tree, typename Node, typename K, typename V>
    friend class BaseTree;
};

#endif
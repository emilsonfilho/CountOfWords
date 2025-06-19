#ifndef INODE_HPP
#define INODE_HPP

template <typename Key, typename Value>
class INode {
public:
    virtual const Key& getKey() const = 0;
    virtual void setKey(const Key& key) = 0;
    virtual ~INode() = default;
};

#endif

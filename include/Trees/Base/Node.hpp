#ifndef INODE_HPP
#define INODE_HPP

#include <sstream>
#include <utility>

/**
 * @brief Represents a basic node that stores a key-value pair.
 *
 * @tparam Key The type of the key.
 * @tparam Value The type of the value.
 */
template <typename Key, typename Value> class Node {
  /**
   * @brief The key-value pair stored in the node.
   */
  std::pair<Key, Value> data;

public:
  /**
   * @brief Constructs a Node with a given key and value.
   *
   * @param key The key to store.
   * @param value The value associated with the key.
   */
  Node(const Key &key, const Value &value) : data({key, value}) {}

  /**
   * @brief Gets the key stored in the node.
   *
   * @return A constant reference to the key.
   */
  const Key &getKey() const { return data.first; }

  /**
   * @brief Sets the key in the node.
   *
   * @param key The new key to assign.
   */
  void setKey(const Key &key) { data.first = key; }

  /**
   * @brief Gets the value stored in the node (read-only).
   *
   * @return A constant reference to the value.
   */
  const Value &getValue() const { return data.second; }

  /**
   * @brief Gets the value stored in the node (modifiable).
   *
   * @return A reference to the value.
   */
  Value &getValue() { return data.second; }

  /**
   * @brief Sets the value in the node.
   *
   * @param value The new value to assign.
   */
  void setValue(const Value &value) { data.second = value; }

  /**
   * @brief Updates both the key and the value of the node.
   *
   * @param key The new key to assign.
   * @param value The new value to assign.
   */
  void update(const Key &key, const Value &value) {
    setKey(key);
    setValue(value);
  }

  /**
   * @brief Returns a string representation of the node as (key, value).
   *
   * @return A formatted string showing the key and value.
   */
  std::string show() const {
    std::ostringstream os;
    os << "(" << getKey() << ", " << getValue() << ")";
    return os.str();
  }

  /**
   * @brief Default destructor.
   */
  ~Node() = default;
};

#endif

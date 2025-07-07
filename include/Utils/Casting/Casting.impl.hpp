#include "Utils/Casting/Casting.hpp"

namespace Casting {
template <typename Key, typename Value, typename Impl>
const IDictionary<Key, Value> &toIDictionary(const Impl &impl) {
  return static_cast<const IDictionary<Key, Value> &>(impl);
}
} // namespace Casting
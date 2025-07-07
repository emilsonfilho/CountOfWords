#include "Utils/Casting/Casting.hpp"

namespace Casting {
DictionaryType toDictionaryType(const std::string &str) {
  try {
    return stringDictionaryTypeMap.at(str);
  } catch (const std::out_of_range &e) {
    throw DictionaryTypeNotFoundException();
  }
}
} // namespace Casting
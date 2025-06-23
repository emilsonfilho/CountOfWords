#include "Utils/StringHandler.hpp"

#include <sstream>

namespace StringHandler {
    template <typename Object>
    std::string toString(const Object& obj) {
        std::ostringstream oss;
        oss << obj;
        return oss.str();
    }
}
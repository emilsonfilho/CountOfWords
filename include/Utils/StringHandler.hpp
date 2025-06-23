#ifndef STRING_HANDLER_HPP
#define STRING_HANDLER_HPP

#include <string>

namespace StringHandler {
    template <typename Object>
    std::string toString(const Object& obj);
}

#include "Utils/StringHandler.impl.hpp"

#endif
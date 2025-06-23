#ifndef STRING_HANDLER_HPP
#define STRING_HANDLER_HPP

#include <string>

namespace StringHandler {
    template <typename Object>
    struct SetWidthAtLeft {
        const Object& obj;
        size_t width;

        SetWidthAtLeft(const Object& o, size_t w)
            : obj(o), width(w) {}
    };

    template <typename Object>
    std::string toString(const Object& obj);
    
    template <typename Object>
    size_t size(const Object& obj);

    template <typename Object>
    std::ostream& operator<<(std::ostream& os, const SetWidthAtLeft<Object>& manip);
}

#include "Utils/StringHandler.impl.hpp"

#endif
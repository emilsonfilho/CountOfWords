#include "Utils/StringHandler.hpp"

#include <sstream>

#include "Utils/StringDictionaryTypeMap.hpp"
#include "Exceptions/FactoryExceptions.hpp"

#include "utf8.h"

namespace StringHandler {
    template <typename Object>
    std::string toString(const Object& obj) {
        std::ostringstream oss;
        oss << obj;
        return oss.str();
    }

    template <typename Object>
    size_t size(const Object& obj) {
        std::string str = toString(obj);
        size_t count = 0;

        auto it = str.begin();
        auto end = str.end();

        while (it != end) {
            utf8::next(it, end);
            count++;
        }

        return count;
    }

    template <typename Object>
    std::ostream& operator<<(std::ostream& os, const SetWidthAtLeft<Object>& manip) {
        std::string str = toString(manip.obj);

        size_t realSize = StringHandler::size(manip.obj),
            padding = (manip.width > realSize ? manip.width - realSize : 0);

        os << str << std::string(padding, ' ');

        return os;
    }

    DictionaryType toDictionaryType(const std::string& str) {
        try {
            return stringDicitionaryTypeMap.at(str);
        } catch(const std::out_of_range& e) {
            throw DictionaryTypeNotFound();
        }
    }
}
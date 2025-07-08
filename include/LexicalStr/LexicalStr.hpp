#ifndef LEXICAL_STR_HPP
#define LEXICAL_STR_HPP

#include <functional>
#include <string>

#include <boost/locale.hpp>
#include "Configs/Locale/Locale.hpp"
#include "Configs/Locale/LocaleSingleton.hpp"

struct LexicalStr {
    std::string data;

    LexicalStr() : data("") {}
    LexicalStr(const std::string& str)
        : data(str) {}
    LexicalStr(const char* str)
        : data(str) {}

    bool operator<(const LexicalStr& other) const {
        return LocaleSingleton::getComparator()(data, other.data);
    }

    bool operator>(const LexicalStr& other) const {
        return other < *this;
    }

    bool operator<=(const LexicalStr& other) const {
        return !(other < *this);
    }

    bool operator>=(const LexicalStr& other) const {
        return !(*this < other);
    }

    bool operator==(const LexicalStr& other) const {
        return data == other.data;
    }

    bool operator!=(const LexicalStr& other) const {
        return !(*this == other);
    }

    explicit operator const std::string&() const {
        return data;
    }

    friend std::ostream& operator<<(std::ostream& os, const LexicalStr& s) {
        return os << s.data;
    }
};

namespace std {
    template<>
    struct hash<LexicalStr> {
        std::size_t operator()(const LexicalStr& key) const noexcept {
            return std::hash<std::string>{}(key.data);
        }
    };
}

#endif
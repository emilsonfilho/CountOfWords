#ifndef LEXICAL_STR_HPP
#define LEXICAL_STR_HPP

#include <functional>
#include <string>

#include <boost/locale.hpp>
#include "Configs/Locale/Locale.hpp"
#include "Configs/Locale/LocaleManager.hpp"

struct LexicalStr {
    std::string data;

    LexicalStr();
    LexicalStr(const std::string& str);
    LexicalStr(const char* str);

    bool operator<(const LexicalStr& other) const;

    bool operator>(const LexicalStr& other) const;

    bool operator<=(const LexicalStr& other) const;

    bool operator>=(const LexicalStr& other) const;

    bool operator==(const LexicalStr& other) const;

    bool operator!=(const LexicalStr& other) const;

    explicit operator const std::string&() const;

    friend std::ostream& operator<<(std::ostream& os, const LexicalStr& s);
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
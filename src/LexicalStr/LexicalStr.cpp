#include "LexicalStr/LexicalStr.hpp"

LexicalStr::LexicalStr() : data("") {}

LexicalStr::LexicalStr(const std::string& str): data(str) {}

LexicalStr::LexicalStr(const char* str): data(str) {}

bool LexicalStr::operator<(const LexicalStr& other) const {
    return LocaleSingleton::getComparator()(data, other.data);
}

bool LexicalStr::operator>(const LexicalStr& other) const {
    return other < *this;
}

bool LexicalStr::operator<=(const LexicalStr& other) const {
    return !(other < *this);
}

bool LexicalStr::operator>=(const LexicalStr& other) const {
    return !(*this < other);
}

bool LexicalStr::operator==(const LexicalStr& other) const {
    return data == other.data;
}

bool LexicalStr::operator!=(const LexicalStr& other) const {
    return !(*this == other);
}

LexicalStr::operator const std::string&() const {
    return data;
}

std::ostream& operator<<(std::ostream& os, const LexicalStr& s) {
    return os << s.data;
}

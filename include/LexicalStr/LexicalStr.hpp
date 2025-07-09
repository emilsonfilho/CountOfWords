#ifndef LEXICAL_STR_HPP
#define LEXICAL_STR_HPP

#include <functional>
#include <string>

#include <boost/locale.hpp>
#include "Configs/Locale/Locale.hpp"
#include "Configs/Locale/LocaleManager.hpp"
/**
 * @struct LexicalStr
 * @brief Wrapper for std::string with custom comparison operators.
 *
 * This structure is designed to represent strings that support full lexical comparisons,
 * possibly based on locale-specific or dictionary-based ordering, depending on how
 * the operators are implemented.
 *
 * It includes full relational and equality operators, explicit conversion to `std::string`,
 * and support for hashing via `std::hash`.
 */
struct LexicalStr {
    /**
     * @brief The actual string data.
     */
    std::string data;

    /**
     * @brief Default constructor.
     */
    LexicalStr();

    /**
     * @brief Constructs a LexicalStr from a std::string.
     * @param str The string to wrap.
     */
    LexicalStr(const std::string& str);

    /**
     * @brief Constructs a LexicalStr from a C-style string.
     * @param str The C-string to wrap.
     */
    LexicalStr(const char* str);

    /**
     * @brief Less-than comparison operator.
     * @param other The other LexicalStr to compare with.
     * @return true if this < other.
     */
    bool operator<(const LexicalStr& other) const;

    /**
     * @brief Greater-than comparison operator.
     * @param other The other LexicalStr to compare with.
     * @return true if this > other.
     */
    bool operator>(const LexicalStr& other) const;

    /**
     * @brief Less-than or equal comparison operator.
     * @param other The other LexicalStr to compare with.
     * @return true if this <= other.
     */
    bool operator<=(const LexicalStr& other) const;

    /**
     * @brief Greater-than or equal comparison operator.
     * @param other The other LexicalStr to compare with.
     * @return true if this >= other.
     */
    bool operator>=(const LexicalStr& other) const;

    /**
     * @brief Equality comparison operator.
     * @param other The other LexicalStr to compare with.
     * @return true if this == other.
     */
    bool operator==(const LexicalStr& other) const;

    /**
     * @brief Inequality comparison operator.
     * @param other The other LexicalStr to compare with.
     * @return true if this != other.
     */
    bool operator!=(const LexicalStr& other) const;

    /**
     * @brief Converts LexicalStr to const std::string&.
     * @return A reference to the internal string.
     */
    explicit operator const std::string&() const;

    /**
     * @brief Stream insertion operator.
     * @param os The output stream.
     * @param s The LexicalStr to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const LexicalStr& s);
};

/**
 * @brief Specialization of std::hash for LexicalStr.
 *
 * Allows LexicalStr to be used as a key in unordered containers like
 * std::unordered_map or std::unordered_set.
 */
namespace std {
    template<>
    struct hash<LexicalStr> {
        /**
         * @brief Computes the hash value of a LexicalStr.
         * @param key The LexicalStr to hash.
         * @return A hash code based on its internal string.
         */
        std::size_t operator()(const LexicalStr& key) const noexcept {
            return std::hash<std::string>{}(key.data);
        }
    };
}

#endif
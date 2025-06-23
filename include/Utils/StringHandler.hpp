#ifndef STRING_HANDLER_HPP
#define STRING_HANDLER_HPP

#include <string>

namespace StringHandler {
    /**
     * @brief A manipulator to set the width and left-align an object when streamed.
     * @tparam Object The type of the object to be formatted.
     */
    template <typename Object>
    struct SetWidthAtLeft {
        const Object& obj; ///< The object to be formatted.
        size_t width;      ///< The desired total width for the formatted output.

        /**
         * @brief Constructs a SetWidthAtLeft manipulator.
         * @param o The object to be formatted.
         * @param w The desired total width for the formatted output.
         */
        SetWidthAtLeft(const Object& o, size_t w)
            : obj(o), width(w) {}
    };


    /**
     * @brief Converts an object to its string representation.
     * @tparam Object The type of the object to convert.
     * @param obj The object to convert.
     * @return The string representation of the object.
     */
    template <typename Object>
    std::string toString(const Object& obj);
    
    /**
     * @brief Determines the "size" or display width of an object, accounting for UTF-8 characters.
     * @tparam Object The type of the object.
     * @param obj The object whose size is to be determined.
     * @return The display width (number of grapheme clusters) of the object's string representation.
     */
    template <typename Object>
    size_t size(const Object& obj);

    /**
     * @brief Overloads the stream insertion operator to apply SetWidthAtLeft formatting.
     * @tparam Object The type of the object contained in the manipulator.
     * @param os The output stream.
     * @param manip The SetWidthAtLeft manipulator.
     * @return A reference to the output stream after formatting.
     */
    template <typename Object>
    std::ostream& operator<<(std::ostream& os, const SetWidthAtLeft<Object>& manip);
}

#include "Utils/StringHandler.impl.hpp"

#endif
#ifndef COLLATE_COMPARE_HPP
#define COLLATE_COMPARE_HPP

#include "Configs/Locale/Locale.hpp"

class CollateCompare {
    std::locale loc;
    const std::collate<char>& coll;
public:
    CollateCompare()
        : loc(Locale().getLang()), coll(std::use_facet<std::collate<char>>(loc)) {}

    template <typename Object>
    int operator()(const Object& a, const Object& b) {
        return coll.compare(
            a.data(), a.data() + a.size(),
            b.data(), b.data() + b.size()
        );
    }
};

#endif
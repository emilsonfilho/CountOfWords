#ifndef LOCALE_SINGLETON_HPP
#define LOCALE_SINGLETON_HPP

#include "Locale.hpp"

#include <boost/locale.hpp>
#include <locale>

class LocaleSingleton {
public:
    static const boost::locale::comparator<char>& getComparator() {
        static boost::locale::generator gen;
        static std::locale loc = gen(Locale::getLang());
        static boost::locale::comparator<char> comp(loc);
        return comp;
    }
};

#endif
#include "Configs/Locale/LocaleSingleton.hpp"

const boost::locale::comparator<char>& LocaleSingleton::getComparator() {
    static boost::locale::generator gen;
    static std::locale loc = gen(Locale::getLang());
    static boost::locale::comparator<char> comp(loc);
    return comp;
}
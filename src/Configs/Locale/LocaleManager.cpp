#include "Configs/Locale/LocaleManager.hpp"

const boost::locale::comparator<char>& LocaleManager::getComparator() {
    static boost::locale::generator gen;
    static std::locale loc = gen(Locale::getLang());
    static boost::locale::comparator<char> comp(loc);
    return comp;
}
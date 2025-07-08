#ifndef LOCALE_SINGLETON_HPP
#define LOCALE_SINGLETON_HPP

#include "Locale.hpp"

#include <boost/locale.hpp>
#include <locale>

/**
 * @class LocaleManager
 * @brief Provides a singleton instance of a locale-aware string comparator.
 *
 * This class ensures that a single instance of a locale-based comparator is used 
 * throughout the application, based on the system or application language settings.
 */
class LocaleManager {
public:
    /**
     * @brief Returns a reference to a locale-aware string comparator.
     *
     * This method creates and caches a `boost::locale::comparator<char>` based on the
     * current locale. It uses `boost::locale::generator` to create the locale using
     * the language returned by `Locale::getLang()`. The comparator respects the 
     * collation rules of the specified language.
     *
     * @return A reference to a singleton comparator for locale-sensitive string comparison.
     */
    static const boost::locale::comparator<char>& getComparator();
};

#endif
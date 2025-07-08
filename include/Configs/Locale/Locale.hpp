#ifndef LOCALE_HPP
#define LOCALE_HPP

#include <string>

inline const char * defaultLocale = "pt_BR.utf8"; // Default locale for Brazilian Portuguese

/**
 * @class Locale
 * @brief Provides utilities related to language and locale settings.
 *
 * This class offers static methods to retrieve locale-specific information,
 * such as the current language setting of the system or application.
 */
class Locale {
public:
    /**
     * @brief Returns the current language setting.
     *
     * This static method retrieves the language code (e.g., "en", "pt") based on
     * the current system or application locale configuration.
     *
     * @return A pointer to a C-style string representing the language code.
     */
    static const char *getLang();
};


#endif
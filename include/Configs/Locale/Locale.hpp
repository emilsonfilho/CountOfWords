#ifndef LOCALE_HPP
#define LOCALE_HPP

#include <string>

inline const char * defaultLocale = "pt_BR.utf8"; // Default locale for Brazilian Portuguese

class Locale {
public:
  static const char *getLang();
};

#endif
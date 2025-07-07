#ifndef LOCALE_HPP
#define LOCALE_HPP

#include <string>

class Locale {
  const char *lang = "pt_BR.utf8"; // Language code for Brazilian Portuguese
public:
  const char *getLang() const;
};

#endif
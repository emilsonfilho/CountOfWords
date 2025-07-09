#include "Configs/Locale/Locale.hpp"

#include <clocale>

#include "Exceptions/LocaleExceptions.hpp"

const char *Locale::getLang() {
  if (!std::setlocale(LC_ALL, defaultLocale))
    throw LocaleNotFoundException();

  return defaultLocale;
}
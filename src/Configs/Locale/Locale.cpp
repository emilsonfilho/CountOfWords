#include "Configs/Locale/Locale.hpp"

#include <clocale>

#include "Exceptions/LocaleExceptions.hpp"

const char *Locale::getLang() const {
  if (!std::setlocale(LC_ALL, lang))
    throw LocaleNotFoundException();

  return lang;
}
#ifndef CLI_OPTIONS_HPP
#define CLI_OPTIONS_HPP

#include <string>

#include "Factory/DictionaryType.hpp"

struct CLIOptions {
    std::string filename;
    std::string inputDict;
    DictionaryType dictType;
};

#endif
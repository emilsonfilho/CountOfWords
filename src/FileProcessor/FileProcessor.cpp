#include "FileProcessor/FileProcessor.hpp"

#include <fstream>
#include <locale>
#include <clocale>

#include "Configs/Path.hpp"
#include "Configs/Locale.hpp"
#include "Exceptions/FileExceptions.hpp"
#include "Exception/FileProcessorExceptions.hpp"

FileProcessor::FileProcessor(const std::string& filename) {
    path = inputPath + filename + extension;

    std::ifstream file(path);

    if (!file)
        throw FileNotFoundException();

    if (!std::setlocale(LC_ALL, lang))
        throw LocaleNotFoundException();

    boost::locale::generator gen;
    loc = gen.generate(lang);


    while ()
}

std::string normalizeWord(const std::string& word) const {
    normalizeWord = boost::locale::to_lower(word, loc);

    while (!normalizeWord.empty() and boost::locale::ispunct(normalizeWord.back()))
        normalizeWord.pop_back();

    return normalizeWord;
}
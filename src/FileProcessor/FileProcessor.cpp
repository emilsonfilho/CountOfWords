#include "FileProcessor/FileProcessor.hpp"

#include <fstream>
#include <clocale>
#include <boost/locale.hpp>

#include <iostream>

#include "Configs/Path.hpp"
#include "Configs/Locale.hpp"
#include "Exceptions/FileExceptions.hpp"
#include "Exceptions/FileProcessorExceptions.hpp"

FileProcessor::FileProcessor(const std::string& filename) {
    path = inputPath + filename + extension;

    std::ifstream file(path);

    if (!file)
        throw FileNotFoundException(path);

    if (!std::setlocale(LC_ALL, lang))
        throw LocaleNotFoundException();

    boost::locale::generator gen;
    loc = gen.generate(lang);

    std::string word;
    while (file >> word)
        words.push_back(normalizeWord(word));
}

std::string FileProcessor::normalizeWord(const std::string& word) const {
    std::string normalizeWord = boost::locale::to_lower(word, loc);

    /**
     * Perhaps this implementation needs to be modified so that the 
     * Bible chapter and verse symbols are separated correctly.
     */
    while (!normalizeWord.empty() and ispunct(static_cast<unsigned char>(normalizeWord.back())))
        normalizeWord.pop_back();

    return normalizeWord;
}
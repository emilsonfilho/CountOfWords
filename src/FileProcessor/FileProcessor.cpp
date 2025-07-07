#include "FileProcessor/FileProcessor.hpp"

#include <boost/locale.hpp>
#include <clocale>
#include <fstream>

#include <iostream>

#include "Configs/Locale/Locale.hpp"
#include "Configs/Path.hpp"
#include "Exceptions/FileExceptions.hpp"

FileProcessor::FileProcessor(const std::string &filename) {
  path = inputPath + filename;

  std::ifstream file(path);

  if (!file)
    throw FileNotFoundException(path);

  boost::locale::generator gen;
  loc = gen.generate(Locale().getLang());

  std::string line;
  while (std::getline(file, line)) {
    auto tokens = tokenize(line);
    for (const auto &word : tokens)
      words.push_back(normalize(word));
  }
}

std::vector<std::string>
FileProcessor::tokenize(const std::string &text) const {
  std::vector<std::string> tokens;

  boost::locale::boundary::ssegment_index tokenMap(
      boost::locale::boundary::word, text.begin(), text.end(), loc);

  tokenMap.rule(boost::locale::boundary::word_any);

  for (auto it = tokenMap.begin(); it != tokenMap.end(); it++) {
    if (!std::all_of(it->begin(), it->end(), [&](char ch) {
          return std::use_facet<std::ctype<char>>(loc).is(
              std::ctype_base::space, ch);
        })) {
      tokens.emplace_back(it->str());
    }
  }

  return tokens;
}

std::string FileProcessor::normalize(const std::string &word) const {
  std::string normalized = word;

  while (isUnderscore(normalized.front()))
    normalized.erase(normalized.begin());

  while (isUnderscore(normalized.back()))
    normalized.pop_back();

  return boost::locale::to_lower(normalized, loc);
}

bool FileProcessor::isUnderscore(char ch) const { return ch == '_'; }
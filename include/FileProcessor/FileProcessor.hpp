#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <vector>
#include <string>

class FileProcessor {
    std::string path;
    std::vector<std::string> words;
    std::locale loc;

    std::string normalizeWord(const std::string& word) const;
public:
    FileProcessor(const std::string& filename);
};

#endif
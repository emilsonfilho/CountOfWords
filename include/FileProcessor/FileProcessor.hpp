#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <vector>
#include <string>
#include <locale>

class FileProcessor {
    std::string path;
    std::locale loc;
    
    std::string normalizeWord(const std::string& word) const;
public:
    std::vector<std::string> words;
    FileProcessor(const std::string& filename);
};

#endif
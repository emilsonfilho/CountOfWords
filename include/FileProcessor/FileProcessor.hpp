#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <vector>
#include <string>

class FileProcessor {
    std::string path;
    std::vector<std::string> words;
public:
    FileProcessor(const std::string& filename);
};

#endif
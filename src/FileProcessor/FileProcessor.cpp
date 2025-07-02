#include "FileProcessor/FileProcessor.hpp"

#include <fstream>

#include "Configs/Path.hpp"
#include "Exceptions/FileExceptions.hpp"

FileProcessor::FileProcessor(const std::string& filename) {
    path = inputPath + filename + extension;

    std::ifstream file(path);

    if (!file)
        throw FileNotFoundException();
}
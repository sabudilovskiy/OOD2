#include "FileHandler.hpp"
#include <exception>

FileHandler::FileHandler(It begin, It end) {
    auto size = end - begin;
    if (size < 2) throw std::logic_error("Путей должно быть как минимум 2");
    read_files.reserve(size - 1);
    for (size_t i = 0; i < size - 1; ++i){
        read_files.emplace_back(begin[i]);
    }
    result = decltype(result){begin[size - 1]};
}

void FileHandler::Do() {
    if (done) return;
    for (auto& file : read_files){
        ReadFile(file);
    }
    WriteResult(result);
    result.close();
}

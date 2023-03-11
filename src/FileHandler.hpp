#pragma once
#include <string>
#include <fstream>
#include <vector>

struct FileHandler{
protected:
    virtual void ReadFile(std::ifstream &file) = 0;
    virtual void WriteResult(std::ofstream& file) = 0;
private:
    std::vector<std::ifstream> read_files;
    std::ofstream result;
    bool done = false;
public:
    using It = std::vector<std::string>::const_iterator;
    FileHandler(It begin, It end);
    void Do();
};
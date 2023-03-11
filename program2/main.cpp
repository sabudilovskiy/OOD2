#include <iostream>
#include <set>
#include <queue>
#include <string>
#include "sstream"
#include "../src/FileHandler.hpp"
#include "Windows.h"

struct MyHandler : FileHandler{
    MyHandler( It begin, It end) : FileHandler(begin, end) {
    }
protected:
    void ReadFile(std::ifstream &file) override {
        std::string temp;
        while (std::getline(file, temp)){
            for (auto elem: temp) {
                buffer << (char) toupper(elem);
            }
            buffer << '\n';
        }
    }
    void WriteResult(std::ofstream &file) override {
       file << buffer.str();
    }
private:
    std::stringstream buffer;
};


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::size_t quality = 0;
    std::string temp;
    while (quality < 2){
        std::cout << "Введите количество файлов: ";
        std::cin >> temp;
        try{
            quality = std::stoull(temp);
            if (quality < 2) throw std::logic_error("должно быть как минимум 2 путей");
        }
        catch (std::exception& exc){
            std::cout << exc.what() << '\n';
        }
    }
    std::vector<std::string> paths;
    paths.reserve(quality);
    std::cin.ignore();
    while (paths.size() < quality){
        std::getline(std::cin, temp);
        paths.emplace_back(std::move(temp));
    }
    MyHandler my_handler{paths.begin(),  paths.end()};
    my_handler.Do();
    std::cout << "Работа выполнена";
    std::cin.get();
}

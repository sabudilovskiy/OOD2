#include <iostream>
#include <set>
#include <queue>
#include <string>
#include "../src/FileHandler.hpp"
#include "Windows.h"

struct MyHandler : FileHandler{
    MyHandler( It begin, It end) : FileHandler(begin + 1, end) {
        std::ifstream file{*begin};
        auto it_file = std::istream_iterator<std::string>{file}, end_file = std::istream_iterator<std::string>{};
        while (it_file != end_file){
            words.emplace(*it_file);
            it_file++;
        }
        auto it = begin + 1;
        while (it != end){
            paths.emplace(*it);
            it++;
        }
    }

protected:
    void ReadFile(std::ifstream &file) override {
        auto path = std::move(paths.front());
        paths.pop();
        auto it_file = std::istream_iterator<std::string>{file}, end_file = std::istream_iterator<std::string>{};
        while (it_file != end_file){
            if (words.find(*it_file) != words.end()){
                founded.emplace(std::move(path));
                break;
            }
        }
    }
    void WriteResult(std::ofstream &file) override {
        while (!founded.empty()){
            auto path = std::move(founded.front());
            founded.pop();
            file << path << '\n';
        }
    }
private:
    std::set<std::string> words;
    std::queue<std::string> paths;
    std::queue<std::string> founded;
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
}

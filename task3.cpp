#include "task3.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace file_processor {


Toy::Toy(const std::string& name, double price, int minAge, int maxAge)
    : name_(name), price_(price), minAge_(minAge), maxAge_(maxAge) {}

bool Toy::isSuitableForAge(int age) const {
    return age >= minAge_ && age <= maxAge_;
}

std::string Toy::toString() const {
    return name_ + " - " + std::to_string(price_) + 
           " руб., возраст: " + std::to_string(minAge_) + 
           "-" + std::to_string(maxAge_);
}


Task3::Task3(const std::string& filePath) : filePath_(filePath) {
    std::ifstream in_file(filePath_, std::ios::binary);
    if (in_file) {
        loadToys();
        in_file.close();
    }
}

void Task3::loadToys() {
    toys_.clear();
    std::ifstream in_file(filePath_, std::ios::binary);
    if (!in_file) {
        return;
    }
    
    while (in_file.peek() != EOF) {
        // Читаем имя
        size_t name_length;
        if (!in_file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length))) {
            break;
        }
        
        std::vector<char> name_buffer(name_length);
        if (!in_file.read(name_buffer.data(), name_length)) {
            break;
        }
        std::string name(name_buffer.data(), name_length);

        double price;
        int min_age, max_age;
        if (!in_file.read(reinterpret_cast<char*>(&price), sizeof(price)) ||
            !in_file.read(reinterpret_cast<char*>(&min_age), sizeof(min_age)) ||
            !in_file.read(reinterpret_cast<char*>(&max_age), sizeof(max_age))) {
            break;
        }
        
        toys_.emplace_back(name, price, min_age, max_age);
    }
    
    in_file.close();
}

void Task3::saveToys() const {
    std::ofstream out_file(filePath_, std::ios::binary);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла: " << filePath_ << std::endl;
        return;
    }
    
    for (const auto& toy : toys_) {
        size_t name_length = toy.getName().length();
        out_file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
        out_file.write(toy.getName().c_str(), name_length);
        
        double price = toy.getPrice();
        int min_age = toy.getMinAge();
        int max_age = toy.getMaxAge();
        
        out_file.write(reinterpret_cast<const char*>(&price), sizeof(price));
        out_file.write(reinterpret_cast<const char*>(&min_age), sizeof(min_age));
        out_file.write(reinterpret_cast<const char*>(&max_age), sizeof(max_age));
    }
    
    out_file.close();
}

void Task3::generateRandomToys(int count) {
    std::vector<std::string> toy_names = {
        "Мяч", "Кукла", "Конструктор", "Машинка", 
        "Паззл", "Кубики", "Мягкая игрушка", "Настольная игра",
        "Плюшевый мишка", "Железная дорога"
    };
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    toys_.clear();
    for (int i = 0; i < count; ++i) {
        std::string name = toy_names[std::rand() % toy_names.size()];
        double price = (std::rand() % 5000 + 100) / 100.0;  // цена 1.00 - 50.00
        int min_age = std::rand() % 3;  // мин возраст 0-2
        int max_age = std::rand() % 5 + 3;  // макс возраст 3-7
        
        toys_.emplace_back(name, price, min_age, max_age);
    }
    
    saveToys();
}

void Task3::addToy(const Toy& toy) {
    toys_.push_back(toy);
    saveToys();
}

bool Task3::findToyForThreeYearOld() const {
    for (const auto& toy : toys_) {
        if (toy.getName() != "Мяч" && toy.isSuitableForAge(3)) {
            std::cout << "  Найдена подходящая игрушка: " << toy.toString() << std::endl;
            return true;
        }
    }
    return false;
}

void Task3::execute() {
    std::cout << "\nЗАДАНИЕ 3: Игрушки для детей" << std::endl;
    std::cout << "Условие: Проверить, можно ли подобрать игрушку (кроме мяча)\n"
              << "         для ребенка 3 лет\n" << std::endl;
    
    generateRandomToys(10);

    std::cout << "Список игрушек в файле (" << filePath_ << "):" << std::endl;
    for (size_t i = 0; i < toys_.size(); ++i) {
        std::cout << "  " << (i+1) << ". " << toys_[i].toString() << std::endl;
    }

    std::cout << "\nПоиск игрушки для 3-летнего ребенка (кроме мяча)..." << std::endl;
    bool found = findToyForThreeYearOld();
    std::cout << "\nРезультат: ";
    if (found) {
        std::cout << "ДА, можно подобрать игрушку" << std::endl;
    } else {
        std::cout << "НЕТ, подходящей игрушки не найдено" << std::endl;
    }
}

} // namespace file_processor
#include "task4.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

namespace file_processor {

Task4::Task4(const std::string& filePath) : filePath_(filePath) {
    loadNumbers();
}

void Task4::loadNumbers() {
    numbers_.clear();
    std::ifstream in_file(filePath_);
    if (!in_file) {
        return;
    }
    
    int num;
    while (in_file >> num) {
        numbers_.push_back(num);
    }
    
    in_file.close();
}

void Task4::saveNumbers() const {
    std::ofstream out_file(filePath_);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла: " << filePath_ << std::endl;
        return;
    }
    
    for (int num : numbers_) {
        out_file << num << std::endl;
    }
    
    out_file.close();
}

void Task4::generateRandomNumbers(int count) {
    numbers_.clear();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int i = 0; i < count; ++i) {
        numbers_.push_back(std::rand() % 201 - 100);  // числа от -100 до 100
    }
    
    saveNumbers();
}

int Task4::findSumOfMinMax() const {
    if (numbers_.empty()) {
        return 0;
    }
    
    int min_value = *std::min_element(numbers_.begin(), numbers_.end());
    int max_value = *std::max_element(numbers_.begin(), numbers_.end());
    
    return min_value + max_value;
}

void Task4::execute() {
    std::cout << "\nЗАДАНИЕ 4: Текстовый файл с числами по одному в строке" << std::endl;
    std::cout << "Условие: В текстовом файле найти сумму максимального и минимального элементов\n" << std::endl;
    
    generateRandomNumbers(15);

    std::cout << "Содержимое файла (" << filePath_ << "):" << std::endl;
    for (size_t i = 0; i < numbers_.size(); ++i) {
        std::cout << "  " << numbers_[i];
        if ((i+1) % 10 == 0) std::cout << std::endl;
    }
    if (numbers_.size() % 10 != 0) std::cout << std::endl;

    int sum = findSumOfMinMax();
    std::cout << "\nСумма минимального и максимального элементов: " << sum << std::endl;
    
    if (!numbers_.empty()) {
        int min_val = *std::min_element(numbers_.begin(), numbers_.end());
        int max_val = *std::max_element(numbers_.begin(), numbers_.end());
        std::cout << "  (Минимальное: " << min_val << ", Максимальное: " << max_val << ")" << std::endl;
    }
}

} // namespace file_processor
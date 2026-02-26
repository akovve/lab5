#include "task5.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

namespace file_processor {

int Task5::NumberLine::sumEven() const {
    int sum = 0;
    for (int num : numbers) {
        if (num % 2 == 0) {
            sum += num;
        }
    }
    return sum;
}

Task5::Task5(const std::string& filePath) : filePath_(filePath) {
    loadLines();
}

void Task5::loadLines() {
    lines_.clear();
    std::ifstream in_file(filePath_);
    if (!in_file) {
        return;
    }
    
    std::string line;
    while (std::getline(in_file, line)) {
        NumberLine number_line;
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            number_line.numbers.push_back(num);
        }
        if (!number_line.numbers.empty()) {
            lines_.push_back(number_line);
        }
    }
    
    in_file.close();
}

void Task5::saveLines() const {
    std::ofstream out_file(filePath_);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла: " << filePath_ << std::endl;
        return;
    }
    
    for (const auto& line : lines_) {
        for (size_t i = 0; i < line.numbers.size(); ++i) {
            out_file << line.numbers[i];
            if (i < line.numbers.size() - 1) {
                out_file << " ";
            }
        }
        out_file << std::endl;
    }
    
    out_file.close();
}

void Task5::generateRandomLines(int lineCount, int maxNumbersPerLine) {
    lines_.clear();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int i = 0; i < lineCount; ++i) {
        NumberLine line;
        int numbers_in_line = std::rand() % maxNumbersPerLine + 1;
        
        for (int j = 0; j < numbers_in_line; ++j) {
            line.numbers.push_back(std::rand() % 101 - 50);  // числа от -50 до 50
        }
        
        lines_.push_back(line);
    }
    
    saveLines();
}

int Task5::sumAllEvenNumbers() const {
    int total_sum = 0;
    for (const auto& line : lines_) {
        total_sum += line.sumEven();
    }
    return total_sum;
}

void Task5::execute() {
    std::cout << "\nЗАДАНИЕ 5: Текстовый файл с числами по несколько в строке" << std::endl;
    std::cout << "Условие: Вычислить сумму четных элементов в файле\n" << std::endl;

    generateRandomLines(10, 5);

    std::cout << "Содержимое файла (" << filePath_ << "):" << std::endl;
    for (const auto& line : lines_) {
        std::cout << "  ";
        for (size_t i = 0; i < line.numbers.size(); ++i) {
            std::cout << line.numbers[i];
            if (i < line.numbers.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    int sum = sumAllEvenNumbers();
    std::cout << "\nСумма четных чисел в файле: " << sum << std::endl;

    int evenCount = 0;
    for (const auto& line : lines_) {
        for (int num : line.numbers) {
            if (num % 2 == 0) evenCount++;
        }
    }
    std::cout << "  (Найдено " << evenCount << " четных чисел)" << std::endl;
}

} // namespace file_processor